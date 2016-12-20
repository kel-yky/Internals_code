//tested
#include "main.h"
#include "stdbool.h"

int motor1 = 0;
int motor2 = 0;
int Lspeed = 5400;  //left
int Rspeed = 5500;  //right motor very slow
int count = 0;
int stage = 0;
int mode = 1;
int length;
char buffer[128] = {0};
const int byte;
int turntime = 1100;

void bluetooth_init(void);
void bluetooth_listener(const u8 byte);
 
 enum STATE
 {
	 BEGIN,
	 SPEEDADJ,
	 STOPR,
	 //STOPL,
	 //STOPR,
	 LOWER,
	 GRIP,
	 PICK,
	 TURNL,
	 HORI,
	 SPEEDADJ2,
	 STOPL2,
	 STOPR2,
	 //ADJ,
	 //STOPPL,
	 //STOPPR,
	 //TOBASKET,
	 //STOPL3,
	 //STOPR3,
	 //TURNL,
	 //FORWARD,
	 //STOP,
	 PUTBASKET,
	 STOP3,
	 TURNR2,
	 //STOPL4,
	 //STOPR4,
	 //TURNR2,
	 //TOEND,
	 //STOPL5,
	 //STOPR5,
	 //TURNR3,
	 //STOPL6,
	 //STOPR6,
	 FORWARD,
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
							pneumatic_control(PNEUMATIC2, 0); //lift
							pneumatic_control(PNEUMATIC3, 0); //open
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if ((get_real_ticks() - stopwatch) > 1000)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
					/*	if (stage == STOPBASKET)
						{
							motor_control(MOTOR2, 0, 0);
							motor_control(MOTOR1, 0, 0);
							pneumatic_control(PNEUMATIC2, 1);
							pneumatic_control(PNEUMATIC3, 1);
							pneumatic_control(PNEUMATIC2, 0);
							if (get_real_ticks() - stopwatch > 2000)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						} */
						if (stage == SPEEDADJ)
						{
							if (stopwatch % 15 == 0)
							{
								Lspeed = Lspeed - 8;
							  if (Lspeed < 0)
								{
									Lspeed = 0;
								}
							}
							motor_control(MOTOR1,1,Lspeed);
							if (get_real_ticks() - stopwatch > 600)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPR)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == LOWER)
						{
							pneumatic_control(PNEUMATIC2, 0);
							if (get_real_ticks() - stopwatch > 5000)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == GRIP)
						{
							pneumatic_control(PNEUMATIC3, 1);
							if (get_real_ticks() - stopwatch > 2000)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == PICK)
						{
							pneumatic_control(PNEUMATIC2, 1);
							if (get_real_ticks() - stopwatch > 2000)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == TURNL) 
						{
							motor_control(MOTOR2, 1, Rspeed); //right
							motor_control(MOTOR1, 0, Lspeed); //left
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == HORI) // = HORi
						{
							if (stopwatch % 20 == 0)
							{
								Lspeed = Lspeed - 2;
							}
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 400)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == SPEEDADJ2)
						{
							if (stopwatch % 15 == 0)
							{
								Lspeed = Lspeed - 8;
								if (Lspeed < 0)
								{
									Lspeed = 0;
								}
							}
							motor_control(MOTOR1, 1, Lspeed);
							if (get_real_ticks() - stopwatch > 300)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
							
						if (stage == STOPL2)
						{
							motor_control(MOTOR1,0,0);
							if (get_real_ticks() - stopwatch > 100)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPR2)
						{
							motor_control(MOTOR2,0,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
			/*			if (stage == ADJ)
						{
							motor_control(MOTOR2, 0, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if (get_real_ticks() - stopwatch > 900)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPPL)
						{
							motor_control(MOTOR1,0,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPPR)
						{
							motor_control(MOTOR2,0,0);
							if (get_real_ticks() - stopwatch > 100)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == TOBASKET)
						{
							motor_control(MOTOR2, 0, Rspeed);
							motor_control(MOTOR1, 0, Lspeed);
							if (get_real_ticks() - stopwatch > 1200) 
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOP)
						{
							motor_control(MOTOR1, 0, 0);
							motor_control(MOTOR2, 0, 0);
							if (get_real_ticks() - stopwatch > 2000)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPL3)
						{
							motor_control(MOTOR1,0,0);
							if (get_real_ticks() - stopwatch > 400)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPR3)
						{
							motor_control(MOTOR2,0,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						} 
						if (stage == TURNL)
						{
							motor_control(MOTOR2, 0, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if (get_real_ticks() - stopwatch > 2700)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == FORWARD)
						{
							motor_control(MOTOR2, 0, Rspeed);
							motor_control(MOTOR1, 0, Lspeed);
							if (get_real_ticks() - stopwatch > 1500)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
							if (stage == STOP)
						{
							motor_control(MOTOR2, 0, 0);
							motor_control(MOTOR1, 0, 0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						} */
						if (stage == PUTBASKET)
						{
							motor_control(MOTOR2, 0, 0);
							motor_control(MOTOR1, 0, 0);
							pneumatic_control(PNEUMATIC3, 0);
							if (get_real_ticks() - stopwatch > 1000)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
					/*	if (stage == BACK2)
						{
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if (get_real_ticks() - stopwatch > 800)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPL4)
						{
							motor_control(MOTOR1,0,0);
							if (get_real_ticks() - stopwatch > 300)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPR4)
						{
							motor_control(MOTOR2,0,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}*/
				/*		if (stage == TURNR2)
						{
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > turntime)
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
							if (get_real_ticks() - stopwatch > 1800)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPL5)
						{
							motor_control(MOTOR1,0,0);
							if (get_real_ticks() - stopwatch > 400)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPR5)
						{
							motor_control(MOTOR2,0,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}*/
					/*	if (stage == STOP2)
						{
							motor_control(MOTOR2, 0, 0);
							motor_control(MOTOR1, 0, 0);
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
							if (get_real_ticks() - stopwatch > turntime)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						} */
						if (stage == STOP3)
						{
							motor_control(MOTOR2, 0, 0);
							motor_control(MOTOR1, 0, 0);
							if (get_real_ticks() - stopwatch > 10000)
							{
								stopwatch = get_real_ticks();
							}
						}
					/*	if (stage == STOPL6)
						{
							motor_control(MOTOR1,0,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPR6)
						{
							motor_control(MOTOR2,0,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}*/
						tft_clear();
						tft_prints(10, 10, "STAGE: %d", stage);
						tft_prints(10, 20, "RUNTIME: %d", get_real_ticks() - stopwatch);
			case 2: 
				while (mode == 2)
				{
						tft_clear();
						tft_prints(10,10,"%s", buffer);
				}
			case 3:
				if (stage == BEGIN)
						{
							pneumatic_control(PNEUMATIC2, 0); //lift
							pneumatic_control(PNEUMATIC3, 0); //open
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if ((get_real_ticks() - stopwatch) > 700)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == SPEEDADJ)
						{
							if (stopwatch % 15 == 0)
							{
								Lspeed = Lspeed - 8;
							  if (Lspeed < 0)
								{
									Lspeed = 0;
								}
							}
							motor_control(MOTOR1,1,Lspeed);
							if (get_real_ticks() - stopwatch > 600)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPR)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage = stage + 4;
							}
						}
						if (stage == TURNL) 
						{
							motor_control(MOTOR2, 1, Rspeed); //right
							motor_control(MOTOR1, 0, Lspeed); //left
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == HORI) // = HORi
						{
							if (stopwatch % 20 == 0)
							{
								Lspeed = Lspeed - 2;
							}
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 400)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == SPEEDADJ2)
						{
							if (stopwatch % 15 == 0)
							{
								Lspeed = Lspeed - 8;
								if (Lspeed < 0)
								{
									Lspeed = 0;
								}
							}
							motor_control(MOTOR1, 1, Lspeed);
							if (get_real_ticks() - stopwatch > 300)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
							
						if (stage == STOPL2)
						{
							motor_control(MOTOR1,0,0);
							if (get_real_ticks() - stopwatch > 100)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == STOPR2)
						{
							motor_control(MOTOR2,0,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage = stage + 2;
							}
						}
						if (stage == TURNR2) 
						{
							motor_control(MOTOR2, 0, Rspeed); //right
							motor_control(MOTOR1, 1, Lspeed); //left
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
						}
						if (stage == FORWARD)
						{
							motor_control(MOTOR1,1,Lspeed);
							motor_control(MOTOR2,1,Rspeed);
							if (get_real_ticks() - stopwatch > 150)
							{
								stopwatch = get_real_ticks();
								stage++;
							}
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
			if (mode == 2)
			{
				mode = 3;
			}
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


