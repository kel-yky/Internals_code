#include "encoder.h"
#include "main.h"

int motor1 = 0;
int motor2 = 0;
int Lspeed = 85;
int Rspeed = 75;
int ticks_img = 0;
int stage = 0;

void bluetooth_listener(const u8 byte) ;

char buffer[128];

int main()
{
	while(1)
	{
		motor_init(71,100,0);
		ticks_init();
		uart_init(COM3, 115200);
		uart_interrupt_init(COM3, &bluetooth_listener);
		adc_init();
		tft_init(2, YELLOW, BLACK);
		
		if (ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
			
			int mode = 1;
			
			switch(mode)
			{
				case 1:
					if (buffer[0] != 0)
					{
						mode++;
						break;
					}
					while (ticks_img < 5000)
					{
						motor_control(MOTOR1, 0, Lspeed);   
						motor_control(MOTOR2, 0, Rspeed);	
					}
					if (ticks_img == 5000)
					{
						motor_control(MOTOR1, 0, 0);
						motor_control(MOTOR2, 0, 0);
						stage++;
					}
					
					if (stage == 1)
					{
						while ((ticks_img >= 5500) && (ticks_img < 8000))  //took 450 as average diameter for now since it's not a square
						{
							motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
							motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
						}
						if (ticks_img == 8000)
						{
							motor_control(MOTOR1, 1, 0);
							motor_control(MOTOR2, 1, 0);
							stage++; //stage 4 end
						}
					}
					
					if(stage == 2) // move towards basket zone
					{
							//500mm per square * 5 / 408mm = 6.12
						while ((ticks_img >= 8500) && (ticks_img < 11000)) 
						{
							motor_control(MOTOR1,0,Lspeed);    // agai]]n assuming 1 is backwards
							motor_control(MOTOR2,0,Rspeed);
						}
						if (ticks_img == 12000)
						{
							motor_control(MOTOR1, 1, 0);
							motor_control(MOTOR2, 1, 0);
							stage++; //stage 5 end
						}
					}
					
					if (stage == 3)
					{
						while ((ticks_img >= 12000) && (ticks_img < 13500))   //took 450 as average diameter for now since it's not a square
						{
							
							motor_control(MOTOR1,1,Lspeed);    // assuming motor 2 on right
							motor_control(MOTOR2,0,Rspeed);    // 1 backwards!
						}
						if (ticks_img == 13500)
						{
							motor_control(MOTOR1, 1, 0);
							motor_control(MOTOR2, 1, 0);
							stage++; //stage 6 end
						}
					}
				
					if (stage == 4)
					{
						while ((ticks_img >= 14000) && (ticks_img < 15500))  //took 450 as average diameter for now since it's not a square
						{
							
							motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
							motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
						}
						if (ticks_img == 15500)
						{
							motor_control(MOTOR1, 1, 0);
							motor_control(MOTOR2, 1, 0);
							stage++;
						}
					}
					
					if(stage == 5) // move towards basket zone
					{
						//500mm per square * 5 / 408mm = 6.12
						while ((ticks_img >= 15500) && (ticks_img < 19000)) 
						{
							
							motor_control(MOTOR1,0,Lspeed);    // again assuming 1 is backwards
							motor_control(MOTOR2,0,Rspeed);
						}
						if (ticks_img == 19000)
						{
							motor_control(MOTOR1, 1, 0);
							motor_control(MOTOR2, 1, 0);
							stage++; // stage 9 end
						}
					}
			
					
					//turn right
			
					if (stage == 6)
					{
						while ((ticks_img >= 19000) && (ticks_img < 20500))   //took 450 as average diameter for now since it's not a square
						{
							motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
							motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
						}
						if (ticks_img == 21000)
						{
							motor_control(MOTOR1, 1, 0);
							motor_control(MOTOR2, 1, 0);
							stage++;
						}
					}
					
				case 2: 
						tft_clear();
						tft_prints(0,0,"%s", buffer);	
			}
		}
	}
}


void bluetooth_listener(const u8 byte) //u8
	{
		if(length == 128)
		{length = 0;}
		buffer[length++] = byte;
		buffer[length] = '\0';
			
		
		if (byte == 'w')  //forward
		{
			motor_control(MOTOR1, 0, 85);
			motor_control(MOTOR2, 0, 75);
		}
		if (byte == 's') //backwards
		{
			motor_control(MOTOR1, 1, 90);
			motor_control(MOTOR2, 1, 90);
		}
		if (byte == 'a') //left
		{
			motor_control(MOTOR1, 1, 50);
			motor_control(MOTOR2, 0, 50); // 0 is forward
		}
		if (byte == 'd') //right
		{
			motor_control(MOTOR1, 0, 50);
			motor_control(MOTOR2, 1, 50); 
		}
		if (byte == 'k') //stop
		{
			motor_control(MOTOR1, 0, 0);
			motor_control(MOTOR2, 0, 0);
		}
		if (byte == 'l') //lift
		{
			pneumatic_control(PNEUMATIC2,0);
		}
		if (byte == 'o') //lower
		{
			pneumatic_control(PNEUMATIC2,1);	
		}
		if (byte == 'g') //grip
		{
			pneumatic_control(PNEUMATIC3,0);
		}
		if (byte == 'r') //release
		{
			pneumatic_control(PNEUMATIC3,1);
		}
		if (byte == 't') //shooT
		{
			pneumatic_control(PNEUMATIC4,0);
		}
		if (byte == 'h') //reset shooter
		{
			pneumatic_control(PNEUMATIC4,1);
		}
	}