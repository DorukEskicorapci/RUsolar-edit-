#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include "main.h"
#include "can_params.h"

// CONSTANTS are defined based on this spec
// https://docs.google.com/document/d/1sJ9VwzolyfRb-tBFXXP6ycqGwgcbOeu7hwbXEH93hWY/edit?tab=t.0#heading=h.u8pdmic8hgeu
#define HEARTBEAT_PARAM_ID 1024

#define PARAM_ID_RANGE_MIN 0
#define PARAM_ID_RANGE_MAX 4095

#define SHARED_IDENTIFICATION_RANGE_MIN 0
#define SHARED_IDENTIFICATION_RANGE_MAX 127

#define SHARED_FAULT_RANGE_MIN 128
#define SHARED_FAULT_RANGE_MAX 255

#define SHARED_STR_BROADCAST_RANGE_MIN 256
#define SHARED_STR_BROADCAST_RANGE_MAX 511

#define RESERVED_RANGE_MIN 512
#define RESERVED_RANGE_MAX 1023

#define GLOBAL_VEHICLE_CMD_RANGE_MIN 1024
#define GLOBAL_VEHICLE_CMD_RANGE_MAX 2047

#define GLOBAL_VEHICLE_PARAMS_RANGE_MIN 2048
#define GLOBAL_VEHICLE_PARAMS_RANGE_MAX 4095

//////////////////////////////////////////////////////////
/////////////////////// TYPES ////////////////////////////
//////////////////////////////////////////////////////////

typedef struct
{
	uint32_t board_state;
	uint32_t system_state;
} identification_params;

typedef union
{
	uint8_t present;
	uint8_t nack : 1, other : 1, runtime : 1, broadcast_conflict : 1, reserved : 4;
} can_errors_t;

typedef struct
{
	can_errors_t errors;
	can_params_t* gv_params;
	uint8_t can_id;
	uint32_t board_type_id;
	uint8_t ttl;
} can_config_t;

//////////////////////////////////////////////////////////
///////////////////// FUNCTIONS //////////////////////////
//////////////////////////////////////////////////////////

void sw3_can_init(CAN_HandleTypeDef* hcan, can_config_t* config);

void sw3_can_error_handler(CAN_HandleTypeDef* hcan);

void sw3_can_interrupt_handler(CAN_HandleTypeDef* hcan);

void sw3_can_loop();

int sw3_set_param_mode(message_mode_t a, can_param_t* b);

int sw3_force_send(can_param_t *);

void sw3_can_set_third_party_callback(void (*callback)(CAN_RxHeaderTypeDef, uint8_t[8]));

/**
 * Update global vehicle CAN's params when the device receives a Global Vehicle command
*/
void sw3_can_set_gv_commands_callback(void (*callback)(uint16_t param_id, uint32_t payload));

void sw3_can_set_shared_params_callback(void (*callback)(CAN_RxHeaderTypeDef header, uint16_t param_id, uint32_t payload));

#endif
