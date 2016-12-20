#include "main.h"
//R

int motor1 = 0;
int motor2 = 0;
int Lspeed = 6100;  //left
int Rspeed = 5000;  //right motor very slow
int count = 0;
int stage = 0;
int mode = 1;
int length;
char buffer[128] = {0};
const int byte;

void bluetooth_init(void);
void bluetooth_listener(const u8 byte);
 
 enum STATE
 {
	 BEGIN,
//	 SPEEDADJ,
	 STOPL,
	 STOPR,
	 LOWER,
	 GRIP,
	 PICK,
	 TURNR,
	 HORI,
	 STOPL2,
	 PUTBASKET,
	 BACK,
	 TURNR2,
	 FORWARD,
	 STOPL3,
	 TURNL,
	 TOEND,
	 STOPL5,
	 STOPR5,
	 FORWARD2,
	 STOP4,
 };
 
int main()
{
	motor_init(143,10000,0);
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
				
						if (stage == BEGIN)
						{
							pneumatic_control(PNEUMATIC2, 1); //lift
							pneumatic_control(PNEUMATIC3, 0); //open
							if (get_real_ticks()- stopwatch % 10 == 0)
							{
								Lspeed = Lspeed - 5;
							  if (Lspeed < 0)
								{
									Lspeed = 0;
								}
							}
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if ((get_real_ticks() - stopwatch) > 1150) //800,500,300
							{
								stopwatch = get_real_ticks();
								stage = STOPL;
							}
						}
						if (stage == STOPL)
						{
							motor_control(MOTOR1,1,0);
							if (get_real_ticks() - stopwatch > 350)
							{
								stopwatch = get_real_ticks();
								stage = STOPR;
							}
						}
							
						if (stage == STOPR)
						{
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 50)
							{
								stopwatch = get_real_ticks();
								stage = LOWER;
							}
						}
						if (stage == LOWER)
						{
							pneumatic_control(PNEUMATIC2, 0);
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage = GRIP;
							}
						}
						if (stage == GRIP)
						{
							pneumatic_control(PNEUMATIC3, 1);
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage = PICK;
							}
						}
						if (stage == PICK)
						{
							pneumatic_control(PNEUMATIC2, 1);
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage = TURNR;
							}
						}
						if (stage == TURNR) 
						{
							motor_control(MOTOR2, 0, Rspeed); //right
							motor_control(MOTOR1, 1, Lspeed); //left
							if (get_real_ticks() - stopwatch > 350)
							{
								stopwatch = get_real_ticks();
								stage = HORI;
							}
						}
						if (stage == HORI) // = HORi
						{
							if (get_real_ticks()- stopwatch % 10 == 0)
							{
								Lspeed = Lspeed - 12;
							  if (Lspeed < 0)
								{
									Lspeed = 0;
								}
							}
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 750)
							{
								stopwatch = get_real_ticks();
								stage = STOPL2;
							}
						}
						if (stage == STOPL2)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 100)
							{
								stopwatch = get_real_ticks();
								stage = PUTBASKET;
							}
						}
							if (stage == PUTBASKET)
						{
							pneumatic_control(PNEUMATIC3, 0);
							if (get_real_ticks() - stopwatch > 5000)
							{
								stopwatch = get_real_ticks();
								stage = BACK;
							}
						}
						if (stage == BACK)
						{
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 0, Rspeed);
							if (get_real_ticks() - stopwatch > 100)
							{
								stopwatch = get_real_ticks();
								stage = TURNR2;
							}
						}
							if (stage == TURNR2)
						{
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 0, Rspeed);
							if (get_real_ticks() - stopwatch > 500)
							{
								stopwatch = get_real_ticks();
								stage = FORWARD;
							}
						}
						if (stage == FORWARD)
						{
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if (get_real_ticks() - stopwatch > 450)
							{
								stopwatch = get_real_ticks();
								stage = STOPL3;
							}
						}
						if (stage == STOPL3)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage = TURNL;
							}
						}	
						if (stage == TURNL)
						{
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 0, Lspeed);
							if (get_real_ticks() - stopwatch > 500)
							{
								stopwatch = get_real_ticks();
								stage = TOEND;
							}
						}
						if (stage == TOEND)
						{
							if (get_real_ticks()- stopwatch % 10 == 0)
							{
								Lspeed = Lspeed - 12;
							  if (Lspeed < 0)
								{
									Lspeed = 0;
								}
							}
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 1800)
							{
								stopwatch = get_real_ticks();
								stage = STOPL5;
							}
						}
						if (stage == STOPL5)
						{
							motor_control(MOTOR1,1,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage = STOPR5;
							}
						}
							
						if (stage == STOPR5)
						{
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage = LOWER;
							}
						}
						if (stage == FORWARD2)
						{
							motor_control(MOTOR2, 0, Rspeed);
							motor_control(MOTOR1, 0, Lspeed);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage = STOP4;
							}
						}
						if (stage == STOP4)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 1000)
							{
								stopwatch = get_real_ticks();
							}
						}
						
						tft_clear();
						tft_prints(10, 10, "STAGE: %d", stage);
						tft_prints(10, 20, "RUNTIME: %d", get_real_ticks() - stopwatch);
			case 2: 
				while (mode == 2)
				{
						tft_clear();
						tft_prints(10,10,"%s", buffer);
				}
			}
	}
}
					
					
							
/*
		tft_clear();
		tft_prints(10, 10, "ticks: %d", get_real_ticks());
		tft_prints(20, 10, "STAGE: %d", stage);
		tft_prints(30, 10, "runtime: %d", stopwatch - get_real_ticks());*/


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
			
		if (byte == 'm') //empty = auto
		{
			mode = 2;
			}
		
		if (byte == 'w')  //forward
		{
			motor_control(MOTOR1, 1, Lspeed);
			motor_control(MOTOR2, 1, Rspeed);
		}
		if (byte == 's') //backwards
		{
			motor_control(MOTOR1, 0, 5000);
			motor_control(MOTOR2, 0, 5000);
		}
		if (byte == 'a') //left
		{
			motor_control(MOTOR1, 0, Lspeed);
			motor_control(MOTOR2, 1, Rspeed); // 0 is forward
		}
		if (byte == 'd') //right
		{
			motor_control(MOTOR1, 1, Lspeed);
			motor_control(MOTOR2, 0, Rspeed); 
		}
		if (byte == 'k') //stop
		{
			motor_control(MOTOR1, 0, 0);
			motor_control(MOTOR2, 0, 0);
		}
		if (byte == 'l') //lift
		{
			pneumatic_control(PNEUMATIC2,1);
		}
		if (byte == 'o') //lower
		{
			pneumatic_control(PNEUMATIC2,0);	
		}
		if (byte == 'g') //grip
		{
			pneumatic_control(PNEUMATIC3,1);
		}
		if (byte == 'r') //release
		{
			pneumatic_control(PNEUMATIC3,0);
		}
		if (byte == 't') //shooT
		{
			pneumatic_control(PNEUMATIC4,1);
		}
		if (byte == 'h') //reset shooter
		{
			pneumatic_control(PNEUMATIC4,0);
		}
	}