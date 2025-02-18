#include "can.h"
#include "main.h"
#include "can_params.h"
#include "stm32f7xx_hal_can.h"

typedef union
{
	struct
	{
		uint16_t id;
		uint32_t value;
		uint16_t reserved;
	};
	uint8_t data[8];
} can_payload_t;

static CAN_HandleTypeDef *can_hcan = NULL;
static uint32_t tx_mailbox;
static CAN_TxHeaderTypeDef can_tx_header;

static can_param_t *gv_params_arr = NULL;
static size_t gv_params_size = sizeof(can_params_t) / sizeof(can_param_t);

// TODO: initialize the variable and check against NULL to make sure it is called
static can_config_t *config = NULL;

static void (*sw3_can_third_party_callback)(CAN_RxHeaderTypeDef, uint8_t[8]) = NULL;
static void (*sw3_can_gv_commands_callback)(uint16_t param_id, uint32_t payload) = NULL;
static void (*sw3_can_shared_params_callback)(CAN_RxHeaderTypeDef, uint16_t param_id, uint32_t payload) = NULL;

static uint8_t hb_message_count = 0;
static uint32_t hb_timestamp = 0;
static uint8_t can_hb_pulse = 0; // 0 is on, 1 is off
static uint8_t hb_pending = 0;

static can_param_t *find_param_by_id(uint16_t id)
{
	for (int i = 0; i < gv_params_size; i++)
	{
		if (id == gv_params_arr[i].PARAM_ID)
		{
			return &gv_params_arr[i];
		}
	}
	return NULL;
}

static HAL_StatusTypeDef send_can_message(uint8_t data[8])
{
	return HAL_CAN_AddTxMessage(can_hcan, &can_tx_header, data, &tx_mailbox);
}

void heartbeat_loop()
{
	if (hb_message_count >= 2)
	{
		hb_timestamp = HAL_GetTick();
		can_hb_pulse = 1;
	}
	if (HAL_GetTick() - hb_timestamp > 250 + config->can_id)
	{
		hb_message_count = 0;
		can_hb_pulse = 0;
	}
	if (HAL_GetTick() - hb_timestamp > 1000 + config->can_id)
	{
		hb_pending = 1;
		hb_message_count++;
		hb_timestamp = HAL_GetTick();
	}
}

void sw3_can_set_third_party_callback(void (*callback)(CAN_RxHeaderTypeDef, uint8_t[8]))
{
	if (callback == NULL)
		return;
	sw3_can_third_party_callback = callback;
}

void sw3_can_set_gv_commands_callback(void (*callback)(uint16_t param_id, uint32_t payload))
{
	if (callback == NULL)
		return;
	sw3_can_gv_commands_callback = callback;
}

void sw3_can_set_shared_params_callback(void (*callback)(CAN_RxHeaderTypeDef, uint16_t param_id, uint32_t payload))
{
	if (callback = NULL)
		return;
	sw3_can_shared_params_callback = callback;
}

void sw3_can_interrupt_handler(CAN_HandleTypeDef *hcan)
{
	static CAN_RxHeaderTypeDef RxHeader;
	static can_payload_t can_payload;
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, can_payload.data) != HAL_OK)
		return;

	if (RxHeader.StdId > 127)
	{ // device is not SW3, call third party callback
		if (sw3_can_third_party_callback == NULL)
			return;
		sw3_can_third_party_callback(RxHeader, can_payload.data);
		return;
	}

	can_param_t *param = find_param_by_id(can_payload.id);

	if (param == NULL)
	{ // Parameter is unknown to this firmware
		return;
	}

	if (param->flags.message_mode == AUTO_BROADCAST ||
		param->flags.message_mode == MANUAL_BROADCAST)
	{
		// Another board is conflicting with this board
		sw3_can_errors.broadcast_conflict = 1;
		return;
	}

	// TODO: should have a util function here to check the range
	if (
		can_payload.id >= SHARED_IDENTIFICATION_RANGE_MIN &&
		can_payload.id <= SHARED_IDENTIFICATION_RANGE_MAX)
	{
		// Identication handler
		if (sw3_can_shared_params_callback == NULL)
			return;

		sw3_can_shared_params_callback(RxHeader, ca_payload.id, can_payload.value);
	}
	else if (
		can_payload.id >= SHARED_FAULT_RANGE_MIN &&
		can_payload.id <= SHARED_FAULT_RANGE_MAX)
	{
		// Fault handler
		if (sw3_can_shared_params_callback == NULL)
			return;

		sw3_can_shared_params_callback(RxHeader, ca_payload.id, can_payload.value);
	}
	else if (
		can_payload.id >= SHARED_STR_BROADCAST_RANGE_MIN &&
		can_payload.id <= SHARED_STR_BROADCAST_RANGE_MAX)
	{
		// String broadcast handler
		if (sw3_can_shared_params_callback == NULL)
			return;

		sw3_can_shared_params_callback(RxHeader, ca_payload.id, can_payload.value);
	}
	else if (
		can_payload.id >= RESERVED_RANGE_MIN &&
		can_payload.id <= RESERVED_RANGE_MIN)
	{
		// Reserver handler
		// For now, do nothing here
	}
	else if (
		can_payload.id >= GLOBAL_VEHICLE_CMD_RANGE_MIN &&
		can_payload.id <= GLOBAL_VEHICLE_CMD_RANGE_MAX)
	{
		// Global vehicle commands handler
		// Detect heartbeat
		if (can_payload.id == HEARTBEAT_PARAM_ID)
		{
			hb_message_count++;
			heartbeat_loop();
		}
		else
		{
			// Something else
			if (sw3_can_gv_commands_callback == NULL)
				return;

			sw3_can_gv_commands_callback(can_payload.id, can_payload.value);
		}
	}
	else if (
		can_payload.id >= GLOBAL_VEHICLE_PARAMS_RANGE_MIN &&
		can_payload.id <= GLOBAL_VEHICLE_PARAMS_RANGE_MAX)
	{
		// Global vehicle params handler
		param->last_value = param->value;

		param->value = can_payload.value;

		param->timestamp = HAL_GetTick();
	}
	else
	{
		// Invalid ID
		return;
	}

	// if (can_payload.id == HEARTBEAT_PARAM_ID) {
	// 	hb_message_count++;
	// 	heartbeat_loop();
	// } else if (can_payload.id > 4095) { // not a valid ID
	// 	return;
	// } else if (can_payload.id >= 2048) { // is a global vehicle parameter
	// 	param->last_value = param->value;
	// 	param->value = can_payload.value;
	// 	param->timestamp = HAL_GetTick();
	// } else if (can_payload.id >= 1024) { // is a global vehicle command
	// 	if (sw3_can_gv_commands_callback == NULL) return;
	// 	sw3_can_gv_commands_callback(can_payload.id, can_payload.value);
	// } else if (can_payload.id >= 512) { // is in the reserved range
	// 	// Reserved
	// } else if (can_payload.id >= 256) { // is a string broadcast
	// 	if (sw3_can_shared_params_callback == NULL) return;
	// 	sw3_can_shared_params_callback(RxHeader, ca_payload.id, can_payload.value);
	// } else if (can_payload.id >= 128) { // is a fault category
	// 	if (sw3_can_shared_params_callback == NULL) return;
	// 	sw3_can_shared_params_callback(RxHeader, ca_payload.id, can_payload.value);
	// } else { // is in the identification range
	// 	if (sw3_can_shared_params_callback == NULL) return;
	// 	sw3_can_shared_params_callback(RxHeader, ca_payload.id, can_payload.value);
	// }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	sw3_can_interrupt_handler(hcan);
}

void sw3_can_error_handler(CAN_HandleTypeDef *hcan)
{
	uint32_t err = HAL_CAN_GetError(hcan);

	// TODO: should handle for each case of error according to ERROR_CODE in stm32f7xx_hal_can.h specification
	// if needed
	if (err)
	{
		sw3_can_errors.other = 1;
	}
	else
	{
		sw3_can_errors.other = 0;
	}
}

void sw3_can_init(CAN_HandleTypeDef *hcan, can_config_t *func_config)
{
	can_hcan = hcan;

	can_tx_header = {
		.StdId = func_config->can_id,
		.IDE = CAN_ID_STD,
		.RTR = CAN_RTR_DATA,
		.DLC = 8,
		.TransmitGlobalTime = DISABLE};

	// Reset CAN errors state
	config = func_config;
	config->errors.present = 0;

	sw3_gv_params_init(config->gv_params);

	gv_params_arr = &config->gv_params;
	gv_params_size = sizeof(can_params_t) / sizeof(can_param_t);

	// Start CAN with given config
	if (HAL_CAN_Start(hcan) != HAL_OK)
	{
		// TODO: do something to report back to telemetry?
	}

	// Turn on interupt for hcan to receive messages on the buffer
	// Whenever the message comes in, it "notifies" us?
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	// TODO: // STM32 G43 removing this comment, I just put here to remember it later

	// Set up filters
	CAN_FilterTypeDef canfilterconfig;

	canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
	canfilterconfig.FilterBank = 18; // which filter bank to use from the assigned ones
	canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	canfilterconfig.FilterIdHigh = 0x000 << 5; // 0x001
	canfilterconfig.FilterIdLow = 0;
	canfilterconfig.FilterMaskIdHigh = 0x000 << 5; // 0x001
	canfilterconfig.FilterMaskIdLow = 0x0000;
	canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
	canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
	canfilterconfig.SlaveStartFilterBank = 20; // how many filters to assign to the CAN1 (master can)

	HAL_CAN_ConfigFilter(hcan, &canfilterconfig);
}

void sw3_can_loop()
{
	heartbeat_loop();
	if (hb_pending)
	{
		static can_payload_t payload;
		payload.id = HEARTBEAT_PARAM_ID_PARAM_ID;
		payload.value = 0;
		if (send_can_message(payload.data) == HAL_OK)
			hb_pending = 0;
	}

	// sends general vehicle params tat are marked for send
	for (int i = 0; i < gv_params_size; i++)
	{
		static can_payload_t payload;

		if (gv_params_arr[i].flags.marked_for_send)
		{
			if (gv_params_arr[i].flags.message_mode != AUTO_BROADCAST ||
				gv_params_arr[i].flags.message_mode != MANUAL_BROADCAST)
			{
				config->errors.runtime = 1;
				continue;
			}
			payload.id = gv_params_arr[i].PARAM_ID;
			payload.id = gv_params_arr[i].value;
			if (send_can_message(payload.data) == HAL_OK)
			{
				gv_params_arr[i].flags.marked_for_send = 0;
			}
		}
	}
}
