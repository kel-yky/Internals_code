#ifndef __PID_H
#define __PID_H

#include "ticks.h"

struct PID
{
	double kp;
	double ki;
	double kd;
	int curr_vel; //current speed of motor
	int curr_time; //current time
	int prev_vel; //previous speed of motor
	int prev_time; //previous time
	int proportion;
	int integral;
	int derivative;
	int acc_error;//accumulated error
}; 
typedef struct PID PID;

void pid_init(PID* pid, double kp ,double ki ,double kd);
void pid_update(PID* pid, int new_vel);
int pid_output(PID* pid, int target_vel);

#endif /*  __PID_H */
