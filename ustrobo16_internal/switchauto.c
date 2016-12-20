#include "encoder.h"
#include "main.h"

int motor1, motor2;
int stage = 0;
int ticks_img = 0;
int count = 0;
int mode = 0;
const int Lspeed = 55;
const int Rspeed = 45;

//manual mode

char buffer[128] = {0};  
int length;
int Ioutput;
int speed[2];
int LeftSpeed, RightSpeed;

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
}
	
/*
void bluetooth_init()
{
	uart_init(COM3, 115200);
	uart_interrupt_init(COM3, &bluetooth_listener);
}
*/

int main()
{
	encoder_init();
	motor_init(71,100,0);
	pneumatic_init();
	
	//manual mode
	ticks_init();
	//bluetooth_init();
	uart_init(COM3, 115200);
	uart_interrupt_init(COM3, &bluetooth_listener);	
	 
	//tft for testing
	tft_init(2,YELLOW,BLACK);
	tft_clear();

	
	while(1)
	{
		if (ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
			encoder_update();
			motor1 = enc_get_vel(1);
			motor2 = enc_get_vel(2);
			
			switch (mode)
		{
			case 0: 
					if(count == 0) {
						pneumatic_control(PNEUMATIC2,0); //lift
						count++;
						
					}
					else if (count == 1)
					{
						pneumatic_control(PNEUMATIC3,0); //open
						count++;
						stage = 1;
					}
					
					
					
					if ((stage == 1) && (count == 2))
					{
						if ((ticks_img > 2000) && (ticks_img <= 8000))
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
					}
					
					
					if (stage == 2) //stage3
					{
						pneumatic_control(PNEUMATIC2,1);
						count++;
						if (count == 3)
						{
							pneumatic_control(PNEUMATIC3,1);
							count++;
						}
						if (count == 4)
						{
							pneumatic_control(PNEUMATIC2,0);
							count++;
						}
						stage++;
					}
					
					if (stage == 3)
					{
						if ((ticks_img > 11000) && (ticks_img <= 13000))
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
							stage++; //stage 4 end
						}
					}
					}
					
					
					if(stage == 4) // move towards basket zone
					{
						if ((ticks_img > 13000) && (ticks_img < 17000))
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
							stage++; //stage 5 end
						}
					}
					}
					
					if (stage == 5)
					{
						if ((ticks_img > 17000) && (ticks_img <= 19000))
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
							stage++; //stage 6 end
						}
					}
				}
					
					if (stage == 6) 
					{
						pneumatic_control(PNEUMATIC3,0); //open
						count++;
						stage++; //stage 7 end
					}
					
					if (stage == 7)
					{
						if ((ticks_img > 19000) && (ticks_img <= 21000))
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
							stage++; //stage 8 end
						}
					}
					}
					
					if (stage == 8)
					{
						if ((ticks_img > 21000) && (ticks_img < 26000))
						{
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
								stage++; // stage 9 end
							}
						}
					}
					
					if (stage == 9)
					{
						if ((ticks_img > 26000) && (ticks_img < 28000))
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
								stage++; //stage 10 end
							}
						}
					}
					
					
					if (buffer[0] != 0)
					{
						mode++;
					}	
					break;	
						 
			case 1: tft_clear();
					tft_prints(0,0,"%s", buffer);
					
		}
		}		 
	}
}