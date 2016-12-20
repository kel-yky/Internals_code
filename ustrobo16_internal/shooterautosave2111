#include "encoder.h"
#include "main.h"
#include "pid.h" 
/*
int kP1 = 10;
int kI1 = 5;
int kD1 = 10;
int kP2 = 10;
int kI2 = 5;
int kD2 = 10;
int SpeedAdjustL = 0;
int SpeedAdjustR = 0;
int motor1;
int motor2;
int Lspeed = 40;
int Rspeed = 40;
int idealSpeed;

struct PID *Left; // declare ShooterPID for left motor
struct PID *Right; // declare ShooterPID for right motor

void Speed_monitor(void); //function prototype
*/
int motor1;
int motor2;
int Lspeed = 70;
int Rspeed = 100;  //right motor very slow
int idealSpeed;


int main()
{
//0 is forward, 1 is backward
encoder_init();
motor_init(71,100,0);
pneumatic_init();
tft_init(2, WHITE, BLACK);
//pid_init(Left, kP1, kI1, kD1);
//pid_init(Right, kP2, kI2, kD2);
int stage = 0;


while(1)
{
	encoder_update();
	motor1 = encoder_count(1);   //number of turns by motor 1 <- not defined
	motor2 = encoder_count(2);   //number of turns by motor 2 <- not defined
	//pid_update(Left, enc_get_vel(1));
	//pid_update(Right, enc_get_vel(2));
	
	//length of field is 4000/2 = 2000mm
	//diameter of wheel = 13cm = 130mm, circumference = 408.4mm
	//number of rotations needed = 4 (or 5 but will crash)
	// alternative: we can set wheel so when it starts counting the error can be accounted - discussion later
	
	//assume robot is facing basket to start with
	
	//raise gripper
	//pneumatic_control(1,0);
	stage = 1; //stage 1 end
	
	if (stage == 1)
	{
		if ((motor1 <= 2000) && (motor2 <= 2000))
		{
			encoder_update();
			//idealSpeed = 80;
			//Speed_monitor();
			motor1 = encoder_count(1);   //number of turns by motor 1 <- not defined
			motor2 = encoder_count(2);   //number of turns by motor 2 <- not defined
			motor_control(MOTOR1, 0, Lspeed);   //update motor speed
			motor_control(MOTOR2, 0, Rspeed);			//this should be 20 when rotation less than 1 so should initiate motor?
			tft_clear();
			tft_prints(0,0, "stage %d %d", stage, motor1);
			tft_prints(0,20, "stage %d %d", stage, motor2);
		}
		else
		{
			motor_control(MOTOR1, 0, 0);
			motor_control(MOTOR2, 0, 0);
			stage++;
		}
	}
	
	
	
	//stage 3 grip basket
	int count = 4;
//	int state_prev = 0; // or 1, depends on how mechan connects wires
/*	pneumatic_control(id,state) //put in values and repeat I guess
	int New_state = state;
	// for loop for pneumatics control.......
	if (New_state != state_prev)   // this is at end to keep count, input for next funtion to run -- set condition
	{
		count++;
	}*/
	stage = 3; //stage 3 end
	
	
	//stage 4 = drag basket & move backwards
	//set condition so code does not run until basket has been picked up
	// assuming it takes 4 times to finish grabbing & securing basket by pneumatics
	
	if ((count == 4) && (stage == 3))  
	{
		if ((motor1 >= 2000) && (motor2 >= 2000))
		{
		if ((motor1 <= 2610) && (motor2 <= 2610))
		{
			encoder_update();
			//idealSpeed = 80;
			//Speed_monitor();
			motor_control(MOTOR1,1,Lspeed);    //  1 is backwards
			motor_control(MOTOR2,1,Rspeed);
			tft_clear();
			tft_prints(0,0, "stage %d, %d", stage, motor1);
			tft_prints(0,20, "stage %d, %d", stage, motor2);
		}
		else
		{
			motor_control(MOTOR1, 1, 0);
			motor_control(MOTOR2, 1, 0);
			stage++; //stage 4 end
		}
	}
}
	
	
	// turning right on spot
	
	if (stage == 4)
	{
		if ((motor1 >= 2610) && (motor2 >= 2610))
		{
		if ((motor1 <= 3060)&& (motor2 <= 3060))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
			//idealSpeed = 50;
			//Speed_monitor();
			motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
			motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
			tft_clear();
			tft_prints(0,0, "stage %d, %d", stage, motor1);
			tft_prints(0,20, "stage %d, %d", stage, motor2);
		}
		else
		{
			motor_control(MOTOR1, 1, 0);
			motor_control(MOTOR2, 1, 0);
			stage++; //stage 5 end
		}
	}
}
	
	//actually better if we have a function for motor control because this is so tedious
	//due to time constraint copy and paste for now
	
	
	if(stage == 5) // move towards basket zone
	{
		if ((motor1 >= 3060)&& (motor2 >= 3060))
		{
			//500mm per square * 5 / 408mm = 6.12
		if ((motor1 <= 5560)&& (motor2 <= 5560))
		{
			encoder_update();
			//idealSpeed = 80;
			//Speed_monitor();
			motor_control(MOTOR1,0,Lspeed);    // agai]]n assuming 1 is backwards
			motor_control(MOTOR2,0,Rspeed);
			tft_clear();
			tft_prints(0,0, "stage %d, %d", stage, motor1);
			tft_prints(0,20, "stage %d, %d", stage, motor2);
		}
		else
		{
			motor_control(MOTOR1, 1, 0);
			motor_control(MOTOR2, 1, 0);
			stage++; //stage 6 end
		}
	}
}
	
	
	//raise grip
	stage = 7; //stage 7 end

	
	
	//turn left towards basket
	
	if (stage == 7)
	{
		if ((motor1 >= 5560)&& (motor2 >= 5560))
		{
		if ((motor1 <= 6010)&& (motor2 <= 6010))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
			//idealSpeed = 50;
			//Speed_monitor();
			motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
			motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
			tft_clear();
			tft_prints(0,0, "stage %d, %d", stage, motor1);
			tft_prints(0,20, "stage %d, %d", stage, motor2);
		}
		else
		{
			motor_control(MOTOR1, 1, 0);
			motor_control(MOTOR2, 1, 0);
			stage++; //stage 8 end
		}
	}
	
//release gripper
	stage = 9; //stage 9 end
	
	
	//turn right
	motor1 = motor2 = 0; //reset values
	if (stage == 9)
	{
		if ((motor1 >= 6010)&& (motor2 >= 6010))
		{
		if ((motor1 <= 6460) && (motor2 <= 6460))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
			//idealSpeed = 50;
			//Speed_monitor();
			motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
			motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
			tft_clear();
			tft_prints(0,0, "stage %d, %d", stage, motor1);
			tft_prints(0,20, "stage %d, %d", stage, motor2);
		}
		else
		{
			motor_control(MOTOR1, 1, 0);
			motor_control(MOTOR2, 1, 0);
			stage++;
		}
	}
}
	
	
	//forward!
	
	if(stage == 10) // move towards basket zone
	{
		if ((motor1 >= 6460) && (motor2 >= 6460))
		{
			//500mm per square * 5 / 408mm = 6.12
		if ((motor1 <= 8960) && (motor2 <= 8960))
		{
			encoder_update();
			//idealSpeed = 80;
			//Speed_monitor();
			motor_control(MOTOR1,0,Lspeed);    // again assuming 1 is backwards
			motor_control(MOTOR2,0,Rspeed);
			tft_clear();
			tft_prints(0,0, "stage 2 %d", encoder_count(1));
			tft_prints(0,20, "stage 2 %d", encoder_count(2));
			tft_prints(0,40, "stage number %d", stage);
		}
		else
		{
			motor_control(MOTOR1, 1, 0);
			motor_control(MOTOR2, 1, 0);
		}
	}
			stage++; // stage 11 end
		tft_clear();
		tft_prints(0,0, "%d", motor1);
		tft_prints(0,20, "%d", motor2);
}
	//final turn to adjust position of shooter -- not enough info now so leave it :D

	
	//turn right

	if (stage == 11)
	{
			if ((motor1 >= 8960) && (motor2 >= 8960))
			{
		if ((motor1 <= 9410) && (motor2 <= 9410))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
			//idealSpeed = 50;
			//Speed_monitor();
			motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
			motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
			tft_clear();
			tft_prints(0,0, "stage 2 %d", encoder_count(1));
			tft_prints(0,20, "stage 2 %d", encoder_count(2));
			tft_prints(0,40, "stage number %d", stage);
		}
		else
		{
			motor_control(MOTOR1, 1, 0);
			motor_control(MOTOR2, 1, 0);
		}
	}
				stage++; //stage 12 end
	}


}
}
}

//---speed adjust----------------------------------------------------------------
/*
		void Speed_monitor(void)
		{
			pid_update(Left, enc_get_vel(1));
			pid_update(Right, enc_get_vel(2));
			SpeedAdjustL = pid_output(Left,idealSpeed);
			SpeedAdjustR = pid_output(Right,idealSpeed);
				
				Lspeed > 100 ? Lspeed = 100 : Lspeed;
				Rspeed > 100 ? Rspeed = 100 : Rspeed;
				Lspeed < 0 ? Lspeed = 0 : Lspeed;
				Rspeed < 0 ? Rspeed = 0 : Rspeed;
				
		}
		*/
