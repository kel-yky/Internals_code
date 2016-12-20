#include "main.h"


int count = 0;
char d[2] = {'w', '\0'};

void uart_listener(const u8 byte)   //input reference for buttons when we finalise app
{
	d[0] = byte;
	if (byte == 'w')
	{
		count++; 
	}
}

int main()
{

	led_init();

	adc_init();
	tft_init(2, WHITE, BLACK);
	ticks_init();
	
	uart_init(COM3,115200);
	uart_interrupt_init(COM3,&uart_listener);

	int a = 0;
	while(1)
	{
		if (get_real_ticks() - a >= 500) {
			uart_tx(COM3, "TEST");
			a = get_real_ticks();
		}
			tft_clear();
					//if (count != 0)
					
						
						tft_prints(0,0,"%s %d", d, count);
						
					 
		
				}
			}
		
