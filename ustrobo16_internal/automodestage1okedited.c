#include "encoder.h"
#include "main.h"

int motor1 = 0;
int motor2 = 0;
int Lspeed = 85;
int Rspeed = 75;  //right motor very slow
int count = 0;
int stage = 0;
 
int main()
{
	//0 is forward, 1 is backward
	motor_init(71,100,0);
	//pneumatic_init();
	tft_init(2, YELLOW, BLACK);


	while(1)
	{
		int ticks_img;
		if(ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
		}
			tft_clear();
			tft_prints(0,0,"%d",stage);
		
		//length of field is 4000/2 = 2000mm
		//diameter of wheel = 13cm = 130mm, circumference = 408.4mm
		
		//stage 2 move forward
		if (stage == 0)
		{
			ticks_reset();
			if(ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
		}
			do
			{
				motor_control(MOTOR1, 0, Lspeed);   
				motor_control(MOTOR2, 0, Rspeed);
				if (ticks_img % 100 == 0)
				{
				tft_clear();
				tft_prints(0,20,"%d",ticks_img);
				}
			} while(ticks_img < 3850);
			
			 if (ticks_img < 3850)
			{
				motor_control(MOTOR1, 0, 0);
				motor_control(MOTOR2, 0, 0);
				stage++;
				tft_clear();
				tft_prints(0,0,"%d",stage);
			}
		}
				
		// turning right on spot
		
		if (stage == 1)
		{
			ticks_reset();
			if(ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
		}
			do  //took 450 as average diameter for now since it's not a square
			{
				motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
				motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
				if (ticks_img % 100 == 0)
				{
				tft_clear();
				tft_prints(0,20,"%d",ticks_img);
				}
				}while (ticks_img < 800);
				
			if (ticks_img == 800)
			{
				motor_control(MOTOR1, 0, 0);
				motor_control(MOTOR2, 1, 0);
				stage++; //stage 4 end
				tft_clear();
				tft_prints(0,0,"%d",stage);
			}
		}

		
/*		if(stage == 2) // move towards basket zone
		{
			ticks_reset();
				//500mm per square * 5 / 408mm = 6.12
			if(ticks_img < 4850)  
			{
				motor_control(MOTOR1,0,Lspeed);    // agai]]n assuming 1 is backwards
				motor_control(MOTOR2,0,Rspeed);
			}
			else if (ticks_img == 4900)
			{
				motor_control(MOTOR1, 0, 0);
				motor_control(MOTOR2, 0, 0);
				stage++; //stage 5 end
				tft_clear();
				tft_prints(0,0,"%d",stage);
			}
		}

		//turn left towards tower		
		if (stage == 3)
		{
			ticks_reset();
			if (ticks_img < 800) //took 450 as average diameter for now since it's not a square
			{
				motor_control(MOTOR1,1,Lspeed);    // assuming motor 2 on right
				motor_control(MOTOR2,0,Rspeed);    // 1 backwards!
			}
			else 
			{
				motor_control(MOTOR1, 1, 0);
				motor_control(MOTOR2, 0, 0);
				stage++; //stage 6 end
				tft_clear();
				tft_prints(0,0,"%d",stage);
			}
		}
		
	//turn right
	if (stage == 4)
	{
		ticks_reset();
			if (ticks_img < 800)  //took 450 as average diameter for now since it's not a square
		{
			motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
			motor_control(MOTOR2,1,Rspeed);    // 1 backwards!
		}
			else 
		{
			motor_control(MOTOR1, 0, 0);
			motor_control(MOTOR2, 1, 0);
			stage++;
			tft_clear();
			tft_prints(0,0,"%d",stage);
		}
	}

		
		//forward!
		
		if(stage == 5) // move towards end zone
		{
			ticks_reset();
			//500mm per square * 5 / 408mm = 6.12
			if (ticks_img < 4850) 
			{
				motor_control(MOTOR1,0,Lspeed);    // again assuming 1 is backwards
				motor_control(MOTOR2,0,Rspeed);
			}
			else 
			{
				motor_control(MOTOR1, 1, 0);
				motor_control(MOTOR2, 1, 0);
				stage++; // stage 9 end
				tft_clear();
				tft_prints(0,0,"%d",stage);
			}
		}

		
		//turn right

		if (stage == 6)
		{
			ticks_reset();
			if (ticks_img < 800)   //took 450 as average diameter for now since it's not a square
			{
				motor_control(MOTOR1,0,Lspeed);    // assuming motor 2 on right
				motor_control(MOTOR2,1,Rspeed);  		// 1 backwards!
			}
			else
			{
				motor_control(MOTOR1, 1, 0);
				motor_control(MOTOR2, 1, 0);
				stage++;
			}
		}*/
	}
}