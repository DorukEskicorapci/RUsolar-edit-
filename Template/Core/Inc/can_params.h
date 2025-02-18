#ifndef CAN_PARAMS_H
#define CAN_PARAMS_H

#include "can.h"

typedef struct
{
	can_param_t speed;
} can_params_t;

void sw3_gv_params_init(can_params_t *param);

#endif
