#include "can_params.h"

// Init CAN params
// TODO: should throw these configs into a env file or makefile?
void sw3_gv_params_init(can_params_t *gv_params)
{
	static can_params_t params = {
			.speed = {
					.PARAM_ID = 1025,
					.value = 0,
					.last_value = 0,
					.SAFE_VALUE = 0,
					.timestamp = 0,
					.TTL = 10,
					.flags = {.message_mode = PASSIVE, .marked_for_send = 0, .reserved = 0}
			},
			.led = {
					.PARAM_ID = 2050,
					.value = 0,
					.last_value = 0,
					.SAFE_VALUE = 0,
					.timestamp = 0,
					.TTL = 20,
					.flags = { .message_mode = DEPENCENCY_CALLBACK, .marked_for_send = 0, .reserved = 0}
			}
	};

	*gv_params = params;

}
