#include "encoder.h"
#include "pneumatic.h"
#include "main.h"
/*
int kP1 = 0;
int kI1 = 0;
int kD1 = 0;
int kP2 = 0;
int kI2 = 0;
int kD2 = 0;

struct PID *Left; // declare ShooterPID
struct PID *Right;
*/
int main()
{
//assume 0 is forward, 1 is backward
encoder_init();
motor_init(71,100,0);
pneumatic_init();
tft_init(2, WHITE, BLACK);
//pid_init(&Left, kP1, kI1, kD1);
//pid_init(&Right, kP2, kI2, kD2);
int stage = 0;
int motor1 = encoder_count(1) / 408;   //number of turns by motor 1 <- not defined
	int motor2 = encoder_count(2) / 408;   //number of turns by motor 2 <- not defined
	int Lspeed = 20;
	int Rspeed = 20;

while(1)
{
	tft_clear();
	tft_prints(0,0, "%d", motor1);
	tft_prints(20,0, "%d", motor2);
	//pid_update(&shooterPID, 80)
	//length of field is 4000/2 = 2000mm
	//diameter of wheel = 13cm = 130mm, circumference = 408.4mm
	//number of rotations needed = 4 (or 5 but will crash)
	// alternative: we can set wheel so when it starts counting the error can be accounted - discussion later
	
	//assume robot is facing basket to start with
	
	
	//motor_control(MOTOR1, 0, Lspeed);  
	//motor_control(MOTOR2, 0, Rspeed);
	
	while ((motor1 < 5) && (motor2 < 5))
	{
	//	Speed_monitor(motor1, motor2);  // not sure if I need a variable to store output here?
		
		motor_control(MOTOR1, 1, Lspeed);   //update motor speed
		motor_control(MOTOR2, 1, Rspeed);   //this should be 20 when rotation less than 1 so should initiate motor?
		stage++;
		tft_prints(0,0, "%d", stage);
	}
	//pick up basket
	int count = 0;
//	int state_prev = 0; // or 1, depends on how mechan connects wires
/*	pneumatic_control(id,state) //put in values and repeat I guess
	int New_state = state;
	// for loop for pneumatics control.......
	if (New_state != state_prev)   // this is at end to keep count, input for next funtion to run -- set condition
	{
		count++;
	}
	stage++; */
	stage = 2;
	
	//move backwards
	//set condition so code does not run until basket has been picked up
	motor1 = motor2 = 0; //reset values
	if ((count == 4) && (stage == 2))  // assuming it takes 4 times to finish grabbing & securing basket by pneumatics
	{
	//	Speed_monitor(motor1, motor2);
		motor_control(MOTOR1,0,Lspeed);    //  0 is backwards
		motor_control(MOTOR2,0,Rspeed);
		if ((motor1 == 2) && (motor2 == 2))  // should be more like 1.5, but again cannot be displayed ._.
		{
			stage++;
			break;
		}
	}
	}
	// turning right on spot
	motor1 = motor2 = 0; //reset values
	tft_prints(0,0, "%d", stage);
	if (stage == 3)
	{
		while ((motor1 <= 1)&& (motor2 <= 1))  //took 450 as average diameter for now since it's not a square
		{
			motor_control(MOTOR1,1,50);    // assuming motor 2 on right
			motor_control(MOTOR2,0,50);    // 1 backwards!
		}
		stage++;
	}
	//actually better if we have a function for motor control because this is so tedious
	//due to time constraint copy and paste for now
	
	motor1 = motor2 = 0;
	if(stage == 4) // move towards basket zone
	{
			//500mm per square * 5 / 408mm = 6.12
		while ((motor1 <= 6)&& (motor2 <= 6))
		{
		//	Speed_monitor(motor1, motor2);
			motor_control(MOTOR1,0,Lspeed);    // again assuming 1 is backwards
			motor_control(MOTOR2,0,Rspeed);
		}
		stage++; //not sure which line this should be
		tft_prints(0,0, "%d", stage);
	}
	//stage++?
	
	//turn left towards basket
	motor1 = motor2 = 0;
	if (stage == 5)
	{
		while ((motor1 <= 1)&& (motor2 <= 1))  //took 450 as average diameter for now since it's not a square
		{
			motor_control(MOTOR1,1,50);    // assuming motor 2 on right
			motor_control(MOTOR2,0,50);    // 1 backwards!
		}
		stage++;
		tft_prints(0,0, "%d", stage);
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
		//	Speed_monitor(motor1, motor2);
			motor_control(MOTOR1,0,Lspeed);    // again assuming 1 is backwards
			motor_control(MOTOR2,0,Rspeed);
		}
		stage++; //not sure which line this should be
		tft_prints(0,0, "%d", stage);
	}
	//final turn to adjust position of shooter -- not enough info now so leave it :D
}


//---PID control---------------------------------------------------------------
/*		int PID_control(int error, int P, int I, int D)
		{
				err_acc += error;
				diff = error - err_last;
				err_last = error;
				return P*error + err_acc/I + D*diff;
		}
*/
//---speed adjust----------------------------------------------------------------
/*		int Speed_monitor(int motor1, int motor2)
		{
				int Rot_error = abs(motor1 - motor2); 
				int Speed_Adjust = pid_output(&ShooterPID);
				if (motor1 > motor2)
				{
					Lspeed -= Speed_Adjust;
					Rspeed += Speed_Adjust;
				}
				else
				{
					Lspeed += Speed_Adjust;
					R_speed -= Speed_Adjust; 
				}
				
				Lspeed > 255 ? 255 : Lspeed;
				Rspeed > 225 ? 225 : Rspeed;
				Lspeed < 0 ? 0 : Lspeed;
				Rspeed < 0 ? 0 : Rspeed;
				
				return Lspeed, Rspeed;
		}*/
