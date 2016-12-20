#include "main.h"
//GREEN

int motor1 = 0;
int motor2 = 0;
int Lspeed = 5400;  //left
int Rspeed = 6100;  //right motor very slow
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
	 SPEEDADJ,
	 STOPR,
	 LOWER,
	 GRIP,
	 PICK,
	 TURNR,
	 HORI,
	 SPEEDADJ2,
	 STOPL2,
	 PUTBASKET,
	 TURNR2,
	 FORWARD,
	 STOPL3,
	 TURNL,
	 TOEND,
	 SPEEDADJ3,
	 STOPPP,
	 TURNR3,
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
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if ((get_real_ticks() - stopwatch) > 800)
							{
								stopwatch = get_real_ticks();
								stage = SPEEDADJ;
							}
						}
						if (stage == SPEEDADJ)
						{
							if (get_real_ticks()- stopwatch % 5 == 0)
							{
								Lspeed = Lspeed - 8;
							  if (Lspeed < 0)
								{
									Lspeed = 0;
								}
							}
							motor_control(MOTOR1,1,Lspeed);
							if (get_real_ticks() - stopwatch > 500)
							{
								stopwatch = get_real_ticks();
								stage = STOPR;
							}
						}
						if (stage == STOPR)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 300)
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
							if (get_real_ticks() - stopwatch > 550)
							{
								stopwatch = get_real_ticks();
								stage = HORI;
							}
						}
						if (stage == HORI) // = HORi
						{
							if (stopwatch % 10 == 0)
							{
								Lspeed = Lspeed - 5;
							}
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 800)
							{
								stopwatch = get_real_ticks();
								stage = SPEEDADJ2;
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
								stage = STOPL2;
							}
						}
							
						if (stage == STOPL2)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 400)
							{
								stopwatch = get_real_ticks();
								stage = PUTBASKET;
							}
						}
							if (stage == PUTBASKET)
						{
							pneumatic_control(PNEUMATIC3, 0);
							if (get_real_ticks() - stopwatch > 15000)
							{
								stopwatch = get_real_ticks();
								stage = TURNR2;
							}
						}
							if (stage == TURNR2)
						{
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 0, Rspeed);
							if (get_real_ticks() - stopwatch > 650)
							{
								stopwatch = get_real_ticks();
								stage = FORWARD;
							}
						}
						if (stage == FORWARD)
						{
							motor_control(MOTOR2, 0, Rspeed);
							motor_control(MOTOR1, 0, Lspeed);
							if (get_real_ticks() - stopwatch > 300)
							{
								stopwatch = get_real_ticks();
								stage = STOPL3;
							}
						}
						if (stage == STOPL3)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 1000)
							{
								stopwatch = get_real_ticks();
								stage = TURNL;
							}
						}	
						if (stage == TURNL)
						{
							motor_control(MOTOR2, 0, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if (get_real_ticks() - stopwatch > 900)
							{
								stopwatch = get_real_ticks();
								stage = TOEND;
							}
						}
						if (stage == TOEND)
						{
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 1800)
							{
								stopwatch = get_real_ticks();
								stage = SPEEDADJ3;
							}
						}
						if (stage == SPEEDADJ3)
						{
							if (get_real_ticks()- stopwatch % 15 == 0)
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
								stage = STOPPP;
							}
						}
						if (stage == STOPPP)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 500)
							{
								stopwatch = get_real_ticks();
								stage = TURNR3;
							}
						}
						if (stage == TURNR3)
						{
							motor_control(MOTOR1, 0, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 900)
							{
								stopwatch = get_real_ticks();
								stage = FORWARD2;
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
				/*	
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
						 */
						/*if (stage == STOP3)
						{
							motor_control(MOTOR2, 0, 0);
							motor_control(MOTOR1, 0, 0);
							if (get_real_ticks() - stopwatch > 10000)
							{
								stopwatch = get_real_ticks();
							}
						}*/
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
			/*case 3:
				if (stage == BEGIN)
						{
							pneumatic_control(PNEUMATIC2, 0); //lift
							pneumatic_control(PNEUMATIC3, 0); //open
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if ((get_real_ticks() - stopwatch) > 400)
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
							if (get_real_ticks() - stopwatch > 300)
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
							if (get_real_ticks() - stopwatch > 600)
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
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 1000)
							{
								stopwatch = get_real_ticks();
								stage++;
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
						} */
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


