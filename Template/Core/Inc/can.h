#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include "main.h"

//////////////////////////////////////////////////////////
/////////////////////// TYPES ////////////////////////////
//////////////////////////////////////////////////////////

typedef struct {
	unsigned char message_mode: 4, marked_for_send: 1, reserved: 3;
} internal_flags_t;

// Define CAN message structure
typedef struct {
	// id of the message
	uint16_t PARAM_ID;

	// the message itself -- current message
	uint32_t value;

	// the previous message
	uint32_t last_value;

	// the default value in case we don't receive any messages or something went wrong
	uint32_t SAFE_VALUE;

	uint32_t timestamp;

	// time to live
	uint8_t TTL;

	// some flags to manage the message
	internal_flags_t flags;
} can_param_t;

typedef enum {
	PASSIVE,
	DEPENDENCY_NO_CALLBACK,
	DEPENCENCY_CALLBACK,
	AUTO_BROADCAST,
	MANUAL_BROADCAST
} message_mode_t;

typedef struct {
	uint32_t board_state;
	uint32_t system_state;
} identification_params;

typedef union {
	uint8_t present;
	uint8_t nack: 1, other: 1, runtime: 1, broadcast_conflict: 1, reserved: 4;
} can_errors_t;

extern can_errors_t sw3_can_errors;

//////////////////////////////////////////////////////////
///////////////////// FUNCTIONS //////////////////////////
//////////////////////////////////////////////////////////

void sw3_can_init(CAN_HandleTypeDef*);

void sw3_can_error_handler(CAN_HandleTypeDef* hcan);

void sw3_can_interrupt_handler(CAN_HandleTypeDef* hcan1);

void sw3_can_loop();

int sw3_set_param_mode(message_mode_t, can_param_t*);

int sw3_force_send(can_param_t*);

void sw3_can_set_third_party_callback(void (*callback)(can_param_t*));

#endif
