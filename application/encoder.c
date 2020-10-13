#include "encoder.h"

void encoder_init(encoder_t *enc, TIM_HandleTypeDef *htim)
{
	enc->htim = htim;
}
void encoder_calc(encoder_t *enc, float dt)
{
	enc->ticks_last = enc->ticks;
	enc->ticks = *(int32_t*)(&enc->htim->Instance->CNT);
	enc->pos = (float)enc->ticks*enc->k_ticks_to_real;
	enc->vel_ticks = (float)(enc->ticks - enc->ticks_last)/dt;
	enc->vel = enc->vel_ticks*enc->k_ticks_to_real;
}
