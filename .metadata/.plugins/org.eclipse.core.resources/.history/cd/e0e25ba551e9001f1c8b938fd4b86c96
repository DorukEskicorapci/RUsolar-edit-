#include "can.h"
#include "main.h"
#include "can_params.h"
#include "stm32f7xx_hal_can.h"

typedef union {
	struct {
		uint16_t id;
		uint32_t value;
		uint16_t reserved;
	}
	uint64_t data;
} can_payload_t;

static can_param_t* gv_params_arr = (can_param_t*)&gv_params;
static size_t gv_params_size = sizeof(gv_params)/sizeof(can_param_t);

can_errors_t sw3_can_errors = { .present = 0 };

static void (*sw3_can_third_party_callback)(can_param_t*);

static can_param_t* find(uint16_t id) {
	for(int i = 0; i < gv_params_size; i++) {
		if (id == gv_params_arr[i].PARAM_ID) {
			return gv_params_arr[i];
		}
	}
	return NULL;
}

void sw3_can_set_third_party_callback(void (*callback)(can_param_t*)) {
	if (!callback) return;
	sw3_can_thrid_party_callback = callback;
}

void sw3_can_interrupt_handler(CAN_HandleTypeDef* hcan) {
	static CAN_RxHeaderTypeDef RxHeader;
	static can_payload_t can_payload;
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, can_payload.data) != HAL_OK) return;
	can_param_t* param = find(can_payload.id);
		
	if (!param) { // Parameter is unknown to this firmware
		return;
	} 
	
	if (param->flags.message_mode == AUTO_BROADCAST || 
			param->flags.message_mode == MANUAL_BROADCAST) { // Another board is conflicting with this board
				sw3_can_errors.broadcast_conflict = 1;
				return;
			}

	if (can_payload.id > 4095) { // not a valid ID
		return
	} else if (can_payload.id >= 2048) { // is a global vehicle parameter
		param->last_value = param->value;
		param->value = can_payload.value;
		param->timestamp = HAL_GetTick();
	} else if (can_payload.id >= 1024) { // is a global vehicle command
		// handle global vehicle commands range
	} else if (can_payload.id >= 512) { // is in the reserved range
		// handle reserved range
	} else if (can_payload.id >= 256) { // is a string broadcast
		// handle string broadcast
	} else if (can_payload.id >= 128) { // is a fault category
		// handle fault categories
	} else { // is in the identification range
		
	}

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
	sw3_can_interrupt_handler(hcan);
}

void sw3_can_error_handler(CAN_HandleTypeDef* hcan) {
	uint32_t err = HAL_CAN_GetError(hcan);
	if (err) {
		sw3_can_errors.other = 1;
	} else {
		sw3_can_errors.other = 0;
	}
}

void sw3_can_init(CAN_HandleTypeDef* hcan) {
	// Reset CAN errors state
	sw3_can_errors.present = 0;

	HAL_CAN_Start(hcan);

	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	// Set up filters
	CAN_FilterTypeDef canfilterconfig;

	canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
	canfilterconfig.FilterBank = 18;  // which filter bank to use from the assigned ones
	canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	canfilterconfig.FilterIdHigh = 0x000<<5; // 0x001
	canfilterconfig.FilterIdLow = 0;
	canfilterconfig.FilterMaskIdHigh = 0x000<<5; // 0x001
	canfilterconfig.FilterMaskIdLow = 0x0000;
	canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
	canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
	canfilterconfig.SlaveStartFilterBank = 20;  // how many filters to assign to the CAN1 (master can)

	HAL_CAN_ConfigFilter(hcan, &canfilterconfig);
}
