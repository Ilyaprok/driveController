#ifndef PID_H_
#define PID_H_

#include "main.h"

typedef struct
{
	//public
	float kp, ki, kd;
	float max, min;
	float max_error;
	uint8_t stop;
	float k_ref;
	float freq_cut_LPF_diff;
	float result;

	//private
	float last_error;
	float last_real;
	float smooth_diff;
	uint8_t is_max;
	uint8_t is_min;
	float integral;
}pid_t;

void pid_init(pid_t *pid);
void pid_reset(pid_t *pid);
void pid_calc(pid_t *pid, float ref,float real, float dt);

#endif /* PID_H_ */
