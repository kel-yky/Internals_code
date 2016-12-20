#include "encoder.h"
#include "main.h"

int motor1 = 0;
int motor2 = 0;
int Lspeed = 85;
int Rspeed = 75;  //right motor very slow
/* 
//manual mode

char buffer[128] = {0};  
int length;
int Ioutput;
void  bluetooth_init();
*/ 
int main()
{
	//0 is forward, 1 is backward
	encoder_init();
	motor_init(71,100,0);
	tft_init(2, WHITE, BLACK);

	motor1 = enc_get_vel(1);
	motor2 = enc_get_vel(2);

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
		
		encoder_update();
		motor1 = enc_get_vel(1);   //velocity of motor 1 <- not defined
		motor2 = enc_get_vel(2);   //velocity of motor 2 <- not defined
		
		//length of field is 4000/2 = 2000mm
		//diameter of wheel = 13cm = 130mm, circumference = 408.4mm
		//number of rotations needed = 4 (or 5 but will crash)
		// alternative: we can set wheel so when it starts counting the error can be accounted - discussion later
		
		//assume robot is facing basket to start with
		if (count == 0)
		{
			pneumatic_control(PNEUMATIC2,0); //lift
			count++;
		}
		if (count == 1)
			{
				pneumatic_control(PNEUMATIC3,0); //open
				count++;
				stage++;
			}
		
		
		//stage 2 move forward
		if (stage == 1)
		{
			while (ticks_img < 5000)
			{
				
				encoder_update();
				motor_control(MOTOR1, 0, Lspeed);   
				motor_control(MOTOR2, 0, Rspeed);	
				tft_clear();
				tft_prints(0,0, "stage %d %d", stage, motor1);
				tft_prints(0,20, "stage %d %d", stage, motor2);
			}
			if (ticks_img == 5000)
			{
				motor_control(MOTOR1, 0, 0);
				motor_control(MOTOR2, 0, 0);
				stage++;
			}
		}
		
		//stage 3 grip basket
		if ((stage == 2) && (ticks_img >= 5000))
			{
				if (count == 2)
				{
					pneumatic_control(PNEUMATIC2,1); //down
					count++;
				}
				if (count == 3)
				{
					pneumatic_control(PNEUMATIC3,1); //grip
					count++;
				}
				if (count == 4)
				{
					pneumatic_control(PNEUMATIC2,0); //lift
					count++;
					stage++;
				}
			}
				
		// turning right on spot
		
		if (stage == 3)
		{
			while ((ticks_img >= 7500) && (ticks_img < 9000))  //took 450 as average diameter for now since it's not a square
			{
				encoder_update();
				motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
				motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
				tft_clear();
				tft_prints(0,0, "stage %d, %d", stage, motor1);
				tft_prints(0,20, "stage %d, %d", stage, motor2);
			}
			if (ticks_img == 9000)
			{
				motor_control(MOTOR1, 1, 0);
				motor_control(MOTOR2, 1, 0);
				stage++; //stage 4 end
			}
		}
	
		
		if(stage == 4) // move towards basket zone
		{
				//500mm per square * 5 / 408mm = 6.12
			while ((ticks_img >= 9000) && (ticks_img < 12000)) 
			{
				encoder_update();
				motor_control(MOTOR1,0,Lspeed);    // agai]]n assuming 1 is backwards
				motor_control(MOTOR2,0,Rspeed);
				tft_clear();
				tft_prints(0,0, "stage %d, %d", stage, motor1);
				tft_prints(0,20, "stage %d, %d", stage, motor2);
			}
			if (ticks_img == 12000)
			{
				motor_control(MOTOR1, 1, 0);
				motor_control(MOTOR2, 1, 0);
				stage++; //stage 5 end
			}
		}

		//turn left towards basket		
		if (stage == 5)
		{
			while ((ticks_img >= 12000) && (ticks_img < 13500))   //took 450 as average diameter for now since it's not a square
			{
				encoder_update();
				motor_control(MOTOR1,1,Lspeed);    // assuming motor 2 on right
				motor_control(MOTOR2,0,Rspeed);    // 1 backwards!
				tft_clear();
				tft_prints(0,0, "stage %d, %d", stage, motor1);
				tft_prints(0,20, "stage %d, %d", stage, motor2);
			}
			if (ticks_img == 13500)
			{
				motor_control(MOTOR1, 1, 0);
				motor_control(MOTOR2, 1, 0);
				stage++; //stage 6 end
			}
		}
		
	//release gripper
	if (stage == 6) 
	{
		pneumatic_control(PNEUMATIC3,0); //open
		count++;
		stage++; //stage 7 end
	}
		
		
	//turn right
	if (stage == 7)
	{
		while ((ticks_img >= 14000) && (ticks_img < 15500))  //took 450 as average diameter for now since it's not a square
		{
			encoder_update();
			motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
			motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
			tft_clear();
			tft_prints(0,0, "stage %d, %d", stage, motor1);
			tft_prints(0,20, "stage %d, %d", stage, motor2);
		}
		if (ticks_img == 15500)
		{
			motor_control(MOTOR1, 1, 0);
			motor_control(MOTOR2, 1, 0);
			stage++;
		}
	}

		
		//forward!
		
		if(stage == 8) // move towards basket zone
		{
			//500mm per square * 5 / 408mm = 6.12
			while ((ticks_img >= 15500) && (ticks_img < 19000)) 
			{
				encoder_update();
				motor_control(MOTOR1,0,Lspeed);    // again assuming 1 is backwards
				motor_control(MOTOR2,0,Rspeed);
				tft_clear();
				tft_prints(0,0, "stage %d %d", stage, encoder_count(1));
				tft_prints(0,20, "stage %d %d", stage, encoder_count(2));
			}
			if (ticks_img == 19000)
			{
				motor_control(MOTOR1, 1, 0);
				motor_control(MOTOR2, 1, 0);
				stage++; // stage 9 end
			}
		}

		
		//turn right

		if (stage == 9)
		{
			while ((ticks_img >= 19000) && (ticks_img < 20500))   //took 450 as average diameter for now since it's not a square
			{
				encoder_update();
				motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
				motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
				tft_clear();
				tft_prints(0,0, "stage %d %d", stage, encoder_count(1));
				tft_prints(0,20, "stage %d %d", stage, encoder_count(2));
			}
			if (ticks_img == 21000)
			{
				motor_control(MOTOR1, 1, 0);
				motor_control(MOTOR2, 1, 0);
				stage++;
			}
		}
	}
}
/*
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


	 void bluetooth_init()
	{
		uart_init(COM3, 115200);
		uart_interrupt_init(COM3, &bluetooth_listener);
	}
	*/
