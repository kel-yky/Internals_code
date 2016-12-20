#include "encoder.h"
#include "main.h"

int SpeedAdjustL = 0;
int SpeedAdjustR = 0;
int motor1;
int motor2;
int Lspeed = 65;
int Rspeed = 80;  //right motor very slow

//manual mode

char buffer[128] = {0};  
int length;
int Ioutput;
int kP, kI, kD;
int speed[2];
int LeftSpeed, RightSpeed;
void  bluetooth_init();

int main()
{
//0 is forward, 1 is backward
encoder_init();
motor_init(71,100,0);
pneumatic_init();
tft_init(2, WHITE, BLACK);

int stage = 0;

	//manual mode
	adc_init();
	tft_init(2, WHITE, BLACK);
	ticks_init();
	bluetooth_init();
	motor_init(71,100,0);

	tft_clear();

while(1)
{
	int ticks_img;
	if(ticks_img != get_real_ticks())
	{
		ticks_img = get_real_ticks();
	}
	encoder_update();
	motor1 = enc_get_vel(1);   //velocity of motor 1 <- not defined
	motor2 = enc_get_vel(2);   //velocity of motor 2 <- not defined
	
	if (buffer[0] != 0)				//--------------------
	{
		break;
		}
	
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
		if (ticks_img < 2750)
		{
			if ((motor1 <= 20) && (motor2 <= 20))
			{
				encoder_update();
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
		if ((motor1 <= 20) && (motor2 <= 20))
		{
			encoder_update();
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
		if ((motor1 <= 20)&& (motor2 <= 20))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
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
			//500mm per square * 5 / 408mm = 6.12
		if ((motor1 <= 20)&& (motor2 <= 20))
		{
			encoder_update();
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
	
	
	//raise grip
	pneumatics_control(1,0);
	count++;
	if (count == )
	{
		pneumatics_control(2,0);
		count++;
	}
	
	
	stage = 7; //stage 7 end

	
	
	//turn left towards basket
	
	if (stage == 7)
	{
		if ((motor1 <= 20)&& (motor2 <= 20))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
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
		if ((motor1 <= 20) && (motor2 <= 20))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
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

	
	//forward!
	
	if(stage == 10) // move towards basket zone
	{
			//500mm per square * 5 / 408mm = 6.12
		if ((motor1 <= 20) && (motor2 <= 20))
		{
			encoder_update();
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
			stage++; // stage 11 end
		}
	}

	
	//turn right

	if (stage == 11)
	{
		if ((motor1 <= 20) && (motor2 <= 20))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
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
			stage++;
		}
	}
}


void bluetooth_listener(const u8 byte) //u8
{
	if(length == 128)
	{length = 0;}
	buffer[length++] = byte;
	buffer[length] = '\0';
		
	
	if (byte == 'w')  // int value for forward.w
	{
		motor_control(MOTOR1, 0, 50);
		motor_control(MOTOR2, 0, 50);
	}
	if (byte == 's') //s
	{
		motor_control(MOTOR1, 1, 90);
		motor_control(MOTOR2, 1, 90);
	}
	if (byte == 'a') //a
	{
		motor_control(MOTOR1, 1, 50);
		motor_control(MOTOR2, 0, 50); // I think 0 is forward
	}
	if (byte == 'd') //d
	{
		motor_control(MOTOR1, 0, 50);
		motor_control(MOTOR2, 1, 50); // I think 0 is forward
	}
	if (byte == 'k') //k
	{
		motor_control(MOTOR1, 0, 0);
		motor_control(MOTOR2, 0, 0);
	}
	
while(1)
	{
		tft_clear();
		tft_prints(0,0,"%s", buffer);
	 } 
 }

 void bluetooth_init()
{
	uart_init(COM3, 115200);
	uart_interrupt_init(COM3, &bluetooth_listener);
}