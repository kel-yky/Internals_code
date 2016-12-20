#include "main.h"
#include "encoder.h"

int motor1; 

int main()
{
	motor_init(71,100,0);
	encoder_init();
	tft_init(2,YELLOW,BLUE);
	
	while(1)
	{
		_delay_ms(1000);
		motor_control(MOTOR1,0,100);
		encoder_update();
		motor1 = enc_get_vel(1);
		tft_clear();
		tft_prints(0,0,"%d",motor1);
	}
}
//right 520 when 75
//left 320 when 85
