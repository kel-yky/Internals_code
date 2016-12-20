#include "main.h"
#include "pid.h"
#include "string.h"

char buffer[128];  
int length = 0;

void bluetooth_listener(const u8 byte) //u8
{
	uart_tx(COM3, "%c", byte);
	if(length == 128)
	{length = 0;}
	buffer[length++] = byte;
	buffer[length] = '\0';
}

void bluetooth_init()
{
	uart_init(COM3, 115200);
	uart_interrupt_init(COM3, &bluetooth_listener);
}

int main()
{
	adc_init();
//	tft_init(2, WHITE, BLACK);
	ticks_init();
	bluetooth_init();
	tft_clear();
//	tft_prints(0,0,"0");
	
	while(1)
	{
		tft_clear();
		tft_prints(0,0,"%s", buffer);
	 } 
}
