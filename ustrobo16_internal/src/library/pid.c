/**
 * ================================================================
 * @File: PID.c
 * @author: The most handsome Nicole in the world yeahhhh!
 * @brief: PID.c for robotics team 2016 internal Team 2 (0010) which
 *					 will be providing pid-related functions for 
 *					 shooter auto mode.
 * @version: v1.0
 * ================================================================
 */
#include "PID.h"

/**
 * @param: pid object, kp ,ki and kd
 * @return: none
 * @brief: PID initialization 
 */

void pid_init(PID *pid, double kp ,double ki ,double kd)
{
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	pid->curr_vel = 0;
	pid->curr_time = 0;
	pid->prev_vel = 0;
	pid->prev_time = 0;
	pid->proportion = 0;
	pid->integral = 0;
	pid->derivative = 0;
	pid->acc_error = 0; 
}

/**
 * @param: pid object and the new velocity recorded(from enc_get_vel(int encoder))
 * @return: none
 * @brief: call once during while loop. Save all data to struct
 */
void pid_update(PID* pid, int new_vel )
{
	pid->prev_vel = pid->curr_vel;	
	pid->prev_time = pid->curr_time;
	pid->curr_vel = new_vel;
	pid->curr_time = get_real_ticks(); 
}

/**
 * @param: pid object and the new velocity recorded
 * @return: none
 * @brief: feed target velocity for adjustment(actual output vs real observable output)
 */
int pid_output(PID* pid, int target_vel)
{
	pid-> proportion = pid->kp * (target_vel - pid->curr_vel); 
	
	if(pid->curr_vel == 0)
		return pid->proportion;
		
	pid-> acc_error += (target_vel - pid->curr_vel) * (get_real_ticks() + 1 - pid->curr_time ); 	//+1 to time to prevent the case that the looping is too fast
	pid-> integral = pid->acc_error * pid-> ki;
	pid-> derivative = pid->kd * (pid->curr_vel - pid->prev_vel) / (pid->curr_time - pid->prev_time);
	
	
	return pid->proportion + pid->integral + pid->derivative;
}

/**
 * Following is a sample code for how to use it in main()
 *
 * int main(void)
 * {
 *	PID left;
 *	pid_init(&left, 1, 0, 0);
 *	while(1)
 *	{
 *		pid_update(&left, enc_get_vel());
 *		motor_control(MOTOR1,0, pid_output(&left, 10));
 *	}
 *}
 */
