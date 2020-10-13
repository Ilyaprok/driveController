#ifndef ENCODER_H_
#define ENCODER_H_

#include "main.h"

typedef struct{

	TIM_HandleTypeDef *htim;

	int32_t ticks;
	int32_t ticks_last;
	float pos;
	float vel_ticks;
	float vel;


	float k_ticks_to_real;
}encoder_t;

void encoder_init(encoder_t *enc, TIM_HandleTypeDef *htim);
void encoder_calc(encoder_t *enc, float dt);

#endif /* ENCODER_H_ */
