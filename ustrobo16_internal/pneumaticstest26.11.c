#include "main.h"

int main()
{
	pneumatic_init();
	tft_init(2,YELLOW,BLACK);
	adc_init();
	ticks_init();
	int ticks_img = 0;
	
	while(1)
	{
		if (ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
			}
			if (ticks_img = 1500)
			{
				pneumatic_control(PNEUMATIC2, 1); //lift
				pneumatic_control(PNEUMATIC3, 0);
				}
			if (ticks_img = 3000)
			{
				pneumatic_control(PNEUMATIC2, 0);
			}
			if (ticks_img = 4500)
			{
				pneumatic_control(PNEUMATIC3, 1);
			}
			if (ticks_img = 6000)
			{
			pneumatic_control(PNEUMATIC2, 1);
			}
		}
	}