#include "main.h"
#include "stdbool.h"

int motor1 = 0;
int motor2 = 0;
int Lspeed = 100;
int Rspeed = 65;  //right motor very slow
int count = 0;
int stage = 0;
int mode = 1;
int length;
char buffer[128] = {0};
const int byte;
bool Auto;

void bluetooth_init();
void bluetooth_listener(const u8 byte);
 
 enum STATE
 {
	 BEGIN,
	 STOPBASKET,
	 TURNR,
	 TOBASKET,
	 STOP,
	 TURNL,
	 PUTBASKET,
	 TURNR2,
	 TOEND,
	 STOP2,
	 TURNR3,
 };
 
int main()
{
	motor_init(71,100,0);
	pneumatic_init();
	tft_init(2, YELLOW, BLACK);
	ticks_init();
	adc_init();
	int stopwatch = get_real_ticks();
	bluetooth_init();
	bluetooth_listener(byte);
	
	while(1)
	{
		switch(mode)
		{
			case 1:
							if (Auto == 1)
							{
								mode = 1;
							}
							else
							{
								mode = 2;
								break;
							}
			
						if (stage == BEGIN)
						{
							pneumatic_control(PNEUMATIC2, 0); //lift
							pneumatic_control(PNEUMATIC3, 0); //open
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 0, Rspeed);
							if (get_real_ticks() - stopwatch > 4500)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPBASKET)
						{
							motor_control(MOTOR1, 0, 0);
							motor_control(MOTOR2, 0, 0);
							pneumatic_control(PNEUMATIC2, 1);
							pneumatic_control(PNEUMATIC3, 1);
							pneumatic_control(PNEUMATIC2, 0);
							if (get_real_ticks() - stopwatch > 2000)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == TURNR)
						{
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 600)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == TOBASKET)
						{
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 0, Rspeed);
							if (get_real_ticks() - stopwatch > 4600)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOP)
						{
							motor_control(MOTOR1, 0, 0);
							motor_control(MOTOR2, 0, 0);
							if (get_real_ticks() - stopwatch > 100)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == TURNL)
						{
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 0, Rspeed);
							if (get_real_ticks() - stopwatch > 600)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == PUTBASKET)
						{
							pneumatic_control(PNEUMATIC3, 0);
							if (get_real_ticks() - stopwatch > 100)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == TURNR2)
						{
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 600)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						
						if (stage == TOEND)
						{
							pneumatic_control(PNEUMATIC2, 1);
							pneumatic_control(PNEUMATIC3, 1);
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 0, Rspeed);
							if (get_real_ticks() - stopwatch > 4600)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOP2)
						{
							motor_control(MOTOR1, 0, 0);
							motor_control(MOTOR2, 0, 0);
							if (get_real_ticks() - stopwatch > 100)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == TURNR3)
						{
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 600)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
			case 2: 
				while (Auto == 1)
				{
						tft_clear();
						tft_prints(10,10,"%s", buffer);
				}
	}
}
/*
		tft_clear();
		tft_prints(10, 10, "ticks: %d", get_real_ticks());
		tft_prints(20, 10, "STAGE: %d", stage);
		tft_prints(30, 10, "runtime: %d", stopwatch - get_real_ticks());*/
	}

void bluetooth_init()
{
	uart_init(COM3, 115200);
	uart_interrupt_init(COM3, &bluetooth_listener);	
}

void bluetooth_listener(const u8 byte) //u8
	{
		if(length == 128)
		{length = 0;}
		buffer[length++] = byte;
		buffer[length] = '\0';
			
		if (byte == '0') //empty = auto
		{
			Auto = 1;
		}
		
		if (byte == 'w')  //forward
		{
			motor_control(MOTOR1, 0, Lspeed);
			motor_control(MOTOR2, 0, Rspeed);
		}
		if (byte == 's') //backwards
		{
			motor_control(MOTOR1, 1, 90);
			motor_control(MOTOR2, 1, 90);
		}
		if (byte == 'a') //left
		{
			motor_control(MOTOR1, 1, Lspeed);
			motor_control(MOTOR2, 0, Rspeed); // 0 is forward
		}
		if (byte == 'd') //right
		{
			motor_control(MOTOR1, 0, Lspeed);
			motor_control(MOTOR2, 1, Rspeed); 
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
