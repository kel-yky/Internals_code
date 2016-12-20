#include "main.h"

int main()
{
	ticks_init();
	pneumatic_init();
	tft_init(2, YELLOW, BLACK);
	tft_clear();
	button_init();
	int ticks_img;
	
	while(1)
	{
		
		if (read_button(1) == 0)
		{
				pneumatic_control(PNEUMATIC2, 0);
				tft_clear();
				tft_prints(0,0, "lift");
		}
		if (read_button(1) == 1)
		{
				pneumatic_control(PNEUMATIC2, 1);
				tft_clear();
				tft_prints(0,20, "lower"); 
		}
		if (read_button(2) == 0)
		{
				pneumatic_control(PNEUMATIC3, 0);
				tft_clear();
				tft_prints(0,0, "open");
		}
		if (read_button(2) == 1)
		{
				pneumatic_control(PNEUMATIC3, 1);
				tft_clear();
				tft_prints(0,0, "grip");
		}
		if (read_button(3) == 0)
		{
				pneumatic_control(PNEUMATIC4, 0);
				tft_clear();
				tft_prints(0,0, "shoot");
		}
		if (read_button(3) == 1)
		{
				pneumatic_control(PNEUMATIC4, 1);
				tft_clear();
				tft_prints(0,0, "reset");
		}
	}
}

//PNEUMATIC2
