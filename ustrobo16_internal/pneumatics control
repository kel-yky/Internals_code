#include "main.h"

int main()
{
	ticks_init();
	pneumatic_init();
	tft_init(2, YELLOW, BLACK);
	tft_clear();
	int ticks_img;
	
	while(1)
	{
		if (ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
		}
		tft_prints(0,0,"start test now"); 
if (ticks_img % 100 == 0)
{
				pneumatic_control(1,0);
				tft_prints(0,0, "pneumatic state is 0");
}
	if (ticks_img % 150 == 0)
	{
				pneumatic_control(1,1);
				tft_prints(0,20, "pneumatic state is 1"); 
	}
	}
}