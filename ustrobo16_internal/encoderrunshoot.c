#include "encoder.h"
#include "pneumatic.h"
#include "stdio.h"
#include "motor.h"
#include "stdlib.h"

//assume 0 is forward, 1 is backward
int PID_control(int error, int P, int I, int D); // function prototypev 
void Speed_monitor(int motor1, int motor2);
int stage;
int Lspeed = 20;
int Rspeed = 20;

//---PID values; to be modified-----------------------------------
	int kp = 2;
	int ki = 1;
	int kd = 2;
	
//---PID Initializer----------------------------------------------
	int err_acc=0;
	int err_last=0;
	int diff=0;

int main()
{
	encoder_init();
	motor_init(71,100,0);
	pneumatic_init();
	while(1)
	{
		//length of field is 4000/2 = 2000mm
		//diameter of wheel = 13cm = 130mm, circumference = 408.4mm
		//number of rotations needed = 4 (or 5 but will crash)
		// alternative: we can set wheel so when it starts counting the error can be accounted - discussion later
		
		//assume robot is facing basket to start with
		
		int motor1 = encoder_count(1);   //number of turns by motor 1 <- not defined
		int motor2 = encoder_count(2);   //number of turns by motor 2 <- not defined
		
		while (motor1 && motor2 < 5)
		{
			Speed_monitor(motor1, motor2);  
			
			motor_control(MOTOR1, 0, Lspeed);   //update motor speed
			motor_control(MOTOR2, 0, Rspeed);   
		}
		stage++;
		//pick up basket
		/*int count = 0;
		int state_prev = 0; // or 1, depends on how mechan connects wires
		pneumatic_control(id,state) //put in values and repeat I guess
		int New_state = state;
		// for loop for pneumatics control.......
		if (New_state != state_prev)   // this is at end to keep count, input for next funtion to run -- set condition
		{
			count++;
		}*/
		int count = 4;   //!!!!remove when pneumatics code filled in!!!!
		stage++;
		
		//move backwards
		//set condition so code does not run until basket has been picked up
		motor1 = motor2 = 0; //reset values
		if (count == 4)  // assuming it takes 4 times to finish grabbing & securing basket by pneumatics
		{
			Speed_monitor(motor1, motor2);
			motor_control(MOTOR1,1,Lspeed);    // again assuming 1 is backwards
			motor_control(MOTOR2,1,Rspeed);
			if (motor1 && motor2 == 2)  // should be more like 1.5, but again cannot be displayed ._.
			{
				stage++;
				break;
			}
		}
		// turning right on spot
		motor1 = motor2 = 0; //reset values
		if (stage == 3)
		{
			while (motor1 && motor2 <= 1)  //took 450 as average diameter for now since it's not a square
			{
				motor_control(MOTOR1,0,50);    // assuming motor 2 on right
				motor_control(MOTOR2,1,50);    // 1 backwards!
			}
			stage++;
		}
		//actually better if we have a function for motor control because this is so tedious
		//due to time constraint copy and paste for now
		
		motor1 = motor2 = 0;
		if(stage == 4) // move towards basket zone
		{
				//500mm per square * 5 / 408mm = 6.12
			while (motor1 && motor2 <= 6)
			{
				Speed_monitor(motor1, motor2);
				motor_control(MOTOR1,0,Lspeed);    // again assuming 1 is backwards
				motor_control(MOTOR2,0,Rspeed);
			}
			stage++; //not sure which line this should be
		}
		//stage++?
		
		//turn left towards basket
		motor1 = motor2 = 0;
		if (stage == 5)
		{
			while (motor1 && motor2 <= 1)  //took 450 as average diameter for now since it's not a square
			{
				motor_control(MOTOR1,1,50);    // assuming motor 2 on right
				motor_control(MOTOR2,0,50);    // 1 backwards!
			}
			stage++;
		}
		
		//pneumaticsssssss put down basket
		
		//turn right
		motor1 = motor2 = 0; //reset values
		if (stage == 6)
		{
			while (motor1 && motor2 <= 1)  //took 450 as average diameter for now since it's not a square
			{
				motor_control(MOTOR1,0,50);    // assuming motor 2 on right
				motor_control(MOTOR2,1,50);    // 1 backwards!
			}
			stage++;
		}
		
		//forward!
		motor1 = motor2 = 0;
		if(stage == 7) // move towards basket zone
		{
				//500mm per square * 5 / 408mm = 6.12
			while (motor1 && motor2 <= 6)
			{
				Speed_monitor(motor1, motor2);
				motor_control(MOTOR1,0,Lspeed);    // again assuming 1 is backwards
				motor_control(MOTOR2,0,Rspeed);
			}
			stage++; //not sure which line this should be
		}
		//final turn to adjust position of shooter -- not enough info now so leave it :D
	}
}

	//---PID control---------------------------------------------------------------
			int PID_control(int error, int P, int I, int D)
			{
					err_acc += error;
					diff = error - err_last;
					err_last = error;
					return P*error + err_acc/I + D*diff;
			}

	//---speed adjust----------------------------------------------------------------
			void Speed_monitor(int motor1, int motor2)
			{
					int Rot_error = abs(motor1 - motor2);   //error is difference between 2 motors
					/*
					or maybe we can take difference in time?
					suggestion:
					
					int ticks_img[2] = {0};
					int old_count[2] = {0};
					
					for ( i = 1; i <= 2; i++)
					{
						if (encoder_count(i) != old_count[i];
						{
							if (ticks_img != get_real_ticks());
							{
								ticks_img[i] = get_real_ticks();
							}
							int Time_error = abs (ticks_img[1] - ticks_img[2]);
							>> and then fade errors into pid control... whatever makes it work
						}
					}
					*/
					int Speed_Adjust = PID_control(Rot_error, kp, ki, kd);
					if (motor1 > motor2)
					{
						Lspeed -= Speed_Adjust;
						Rspeed += Speed_Adjust;
					}
					else
					{
						Lspeed += Speed_Adjust;
						Rspeed -= Speed_Adjust; 
					}
					
					Lspeed = (Lspeed > 255) ? 255 : Lspeed; 
					Rspeed = (Rspeed > 225) ? 255 : Rspeed; 
					Lspeed = (Lspeed < 0) ? 0 : Lspeed;
					Rspeed = (Rspeed < 0) ? 0 : Rspeed;
			}