#include "main.h"

int main()
{
	adc_init();
	ticks_init();
	motor_init(71, 100, 0);				
	servo_init(143, 10000, 650);				// 0-65535, 750-middle ; range: 450-1050
	tft_init(1, BLACK, WHITE);	
	
	while(1)
	{
		motor_control(MOTOR1, 1, 25);
		
		if (ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
		}
		if ((ticks_img > 500) && (ticks_img <= 1050))
		{
			servo_control(SERVO1, 730);
		}
		if ((ticks_img > 1050) && (ticks_img <= 1600))
		{
			servo_control(SERVO1, 650);
		}
		if ((ticks_img > 1600) && (ticks_img <= 1950))
		{
			servo_control(SERVO1, 570);
		}
		if ((ticks_img > 1950) && (ticks_img <= 2600))
		{
			servo_control(SERVO1, 650);
		}
		if ((ticks_img > 2600) && (ticks_img <= 3000))
		{
			servo_control(SERVO1, 570);
		}
		if ((ticks_img > 3000) && (ticks_img <= 3700))
		{
			servo_control(SERVO1, 650);
		}
		if ((ticks_img > 3700) && (ticks_img <= 4000))
		{
			servo_control(SERVO1, 730);
		}
		if ((ticks_img > 4000) && (ticks_img <= 5000))
		{
			servo_control(SERVO1, 650);
		}
		if ((ticks_img > 5000) && (ticks_img <= 5750))
		{
			servo_control(SERVO1, 730);
		}
		if ((ticks_img > 5750) && (ticks_img <= 6200))
		{
			servo_control(SERVO1, 650);
		}
	}
}
