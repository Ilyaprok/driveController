#include "pid.h"


void pid_init(pid_t *pid)
{
	pid->max = 1.0f;
	pid->min = -1.0f;
	pid->kp = 0.01f;
	pid->ki = 0.001f;
	pid->kd = 0.001f;
	pid->k_ref = 1.0f;
	pid->freq_cut_LPF_diff = 40.0f;
	pid->result = 0;

	pid->last_error = 0;
	pid->smooth_diff = 0;
	pid->is_max = 0;
	pid->is_min = 0;
	pid->integral = 0;
	pid->stop = 0;
}
void pid_reset(pid_t *pid)
{
	pid->integral = 0;
	pid->result = 0;
	pid->smooth_diff = 0;
	pid->is_max = 0;
	pid->is_min = 0;
}
void pid_calc(pid_t *pid, float ref,float real, float dt)
{
	float error = ref - real;

	if (error > pid->max_error || pid->stop)
	{
		pid->stop = 1;
		pid->result = 0;
		pid->integral = 0;
		pid->smooth_diff = 0;
		pid->is_max = 0;
		pid->is_min = 0;
	}
	else
	{
		float cur_diff_err = pid->k_ref*ref - real;
		float diff = (cur_diff_err - pid->last_error)/dt;
		pid->last_error = cur_diff_err;

		float RC = 1.0f/(pid->freq_cut_LPF_diff);
		float kExp  = dt/(RC+dt);
		pid->smooth_diff = (1.0f-kExp)*pid->smooth_diff + kExp*diff;

		if ((pid->is_max && error < 0)
			||
			(pid->is_min && error > 0)
			||
			(pid->is_max == 0 && pid->is_min == 0))
			pid->integral += pid->ki*error*dt;


		float res = error*pid->kp + pid->integral - pid->smooth_diff*pid->kd;
		if (res > pid->max)
		{
			res = pid->max;
			pid->is_max = 1;
		}
		else if (res < pid->min)
		{
			res = pid->min;
			pid->is_min = 1;
		}
		else
		{
			pid->is_max = 0;
			pid->is_min = 0;
		}
		pid->result = res;
	}

	return pid->result;
}
