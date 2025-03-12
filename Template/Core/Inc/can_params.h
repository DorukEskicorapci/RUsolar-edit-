#ifndef CAN_PARAMS_H
#define CAN_PARAMS_H

#include <stdint.h>

// Mes
typedef enum
{
	PASSIVE,
	DEPENDENCY_NO_CALLBACK,
	DEPENCENCY_CALLBACK,
	AUTO_BROADCAST,
	MANUAL_BROADCAST
} message_mode_t;

typedef struct
{
	unsigned char message_mode : 4, marked_for_send : 1, reserved : 3;// - AUTO_BROADCAST: do not read, send when a change is detected
}// - MANUAL_BROADCAST: do not read, send when an update is manually triggeredternal_flags_t;

// Define CAN message structure
// CAN structure is as follows:
// - (uint16_t) PARAM_ID	: id of the message
// - (uint32_t) value		: the current message
// - (uint32_t) last_value	: the previous message
// - (uint32_t) SAFE_VALUE	: the default value in case we don't receive any messages or something went wrong
// - (uint32_t) timestamp	: timestamp of the message
// - (uint8_t)  TTL			: time-to-live of the message
// - (struct internal_flags_t) flags : some flags of the message // TODO: clearer message
typedef struct
{
	uint16_t PARAM_ID;
	uint32_t value;
	uint32_t last_value;
	uint32_t SAFE_VALUE;
	uint32_t timestamp;
	uint8_t TTL;
	internal_flags_t flags;
} can_param_t;

typedef struct
{
	can_param_t speed;
} can_params_t;

void sw3_gv_params_init(can_params_t *param);

#endif
