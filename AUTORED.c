#include "encoder.h"
#include "PID.h"
#include "main.h"
//R 06:19

int motor1 = 0;
int motor2 = 0;
int Lspeed = 5500;  //left
int Rspeed = 5500;  //right motor very slow
int manL = 5000;
int manR = 5000;
int count = 0;
int stage = 0;
int mode = 1;
int length;
char buffer[128] = {0};
const int byte;
int BLspeed = 5500;
int BRspeed = 5500;
int BSpeedAdjustL = 0;
int BSpeedAdjustR = 0;



/* pid */
double kP1 = 1;
double kI1 = 0.4;
double kD1 = 0;

double kP2 = 1;
double kI2 = 0.76; 
double kD2 = 0;

double kP3 = 1;
double kI3 = 0.4;
double kD3 = 0;

double kP4 = 1;
double kI4 = 1;  
double kD4 = 0;

double kPL = 1;
double kIL = 0.9; //0.6
double kDL = 0;

double kPR = 1;  //1
double kIR = 0.5;  //0.26
double kDR = 0;

int SpeedAdjustL=0;
int SpeedAdjustR=0;
int idealSpeed = 5500;

PID AutoL;
PID AutoR;
PID Left;
PID Right;
PID BLeft;
PID BRight;

void bluetooth_init(void);
void bluetooth_listener(const u8 byte);
void Speed_monitor(void);
void Speed_monitorBACK(void);
void Speed_monitorAUTO(void);


 
 enum STATE
 {
	 BEGIN,
	 STOPR,
	 LOWER,
	 GRIP,
	 PICK,
	 TURNR,
	 HORI,
	 STOP2,
	 PUTBASKET,
	 BACK,
 };
 
int main()
{
	motor_init(143,10000,0);
	pneumatic_init();
	tft_init(2, YELLOW, BLACK);
	ticks_init();
	adc_init();
	int stopwatch = get_real_ticks();
motor2 = encoder_count(1); //right
motor1 = encoder_count(2); //left
	bluetooth_init();
	bluetooth_listener(byte);
	pid_init(&AutoL, kPL, kIL, kDL);
	pid_init(&AutoR, kPR, kIR, kDR);
	pid_init(&Left, kP1, kI1, kD1);
	pid_init(&Right, kP2, kI2, kD2);
	pid_init(&BLeft, kP3, kI3, kD3);
	pid_init(&BRight, kP4, kI4, kD4);
	
	while(1)
	{
		switch(mode)
		{
			case 1:
				
					if (stage == BEGIN)
						{
							if (get_real_ticks() - stopwatch == 20)
							{
							pneumatic_control(PNEUMATIC2, 1); //lift
							}
							_delay_ms(200) ;
							pneumatic_control(PNEUMATIC3, 0); //open
							Speed_monitorAUTO();
							motor_control(MOTOR2, 1, Rspeed);
							motor_control(MOTOR1, 1, Lspeed);
							if ((get_real_ticks() - stopwatch) > 1200) //800,500,300
							{
								stopwatch = get_real_ticks();
								stage = STOPR;
							}
						}
					
						if (stage == STOPR)
						{
							Speed_monitorAUTO();
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 200)
							{
								stopwatch = get_real_ticks();
								stage = LOWER;
							}
						}
						if (stage == LOWER)
						{
							_delay_ms(300);
							if (get_real_ticks() - stopwatch == 50)
							{
							pneumatic_control(PNEUMATIC2, 0);
							}
							if ((get_real_ticks() - stopwatch) > 780)
							{
								stopwatch = get_real_ticks();
								stage = GRIP;
							}
						}
						
							if (stage == GRIP)
						{
							if (get_real_ticks() - stopwatch == 50)
							{
							pneumatic_control(PNEUMATIC3, 1);
							}
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage = PICK;
							}
						}
						if (stage == PICK)
						{
							if (get_real_ticks() - stopwatch == 50)
							{
							pneumatic_control(PNEUMATIC2, 1);
							}
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage = TURNR;
							}
						}
						if (stage == TURNR) 
						{
							Speed_monitorAUTO();
							motor_control(MOTOR1, 0, Lspeed); //left
							motor_control(MOTOR2, 1, Rspeed); //right
							if (get_real_ticks() - stopwatch > 700)
							{
								stopwatch = get_real_ticks();
								stage = HORI;
							}
					}
						if (stage == HORI) // = HORi
						{
							Speed_monitorAUTO();
							motor_control(MOTOR1, 1, Lspeed);
							motor_control(MOTOR2, 1, Rspeed);
							if (get_real_ticks() - stopwatch > 800)
							{
								stopwatch = get_real_ticks();
								stage = STOP2;
							}
						}
						if (stage == STOP2)
						{
							motor_control(MOTOR1,1,0);
							motor_control(MOTOR2,1,0);
							if (get_real_ticks() - stopwatch > 300)
							{
								stopwatch = get_real_ticks();
								stage = PUTBASKET;
							}
							if (stage == PUTBASKET)
						{
							pneumatic_control(PNEUMATIC3, 0);
							if (get_real_ticks() - stopwatch > 15000)
							{
								stopwatch = get_real_ticks();
							}
						}
		
					
			case 2: 
				while (mode == 2)
				{
						tft_clear();
						tft_prints(10,10,"%s", buffer);
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
			}
		
		if (byte == 'w')  //forward
		{
			Speed_monitor();
			motor_control(MOTOR1, 1, manL);
			motor_control(MOTOR2, 1, manR);
		}
		if (byte == 's') //backwards
		{
			Speed_monitorBACK();
			motor_control(MOTOR1, 0, 5000);
			motor_control(MOTOR2, 0, 5000);
		}
		if (byte == 'a') //left
		{
			motor_control(MOTOR1, 0, manL);
			motor_control(MOTOR2, 1, manR); // 0 is forward
		}
		if (byte == 'd') //right
		{
			motor_control(MOTOR1, 1, manL);
			motor_control(MOTOR2, 0, manR); 
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

	
		void Speed_monitor(void)
		{
			pid_update(&Left, enc_get_vel(2));
			pid_update(&Right, enc_get_vel(1));
			SpeedAdjustL = pid_output(&Left,idealSpeed);
			SpeedAdjustR = pid_output(&Right,idealSpeed);
			manL += SpeedAdjustL;
			manR += SpeedAdjustR;
				
				manL > 10000 ? manL = 10000 : manL;
				manR > 10000 ? manR = 10000 : manR;
				manL < 0 ? manL = 0 : manL;
				manR < 0 ? manR = 0 : manR;	
		}
		
		void Speed_monitorBACK(void)
		{
			pid_update(&BLeft, enc_get_vel(2));
			pid_update(&BRight, enc_get_vel(1));
			SpeedAdjustL = pid_output(&BLeft,idealSpeed);
			SpeedAdjustR = pid_output(&BRight,idealSpeed);
			BLspeed += BSpeedAdjustL;
			BRspeed += BSpeedAdjustR;
				
				BLspeed > 10000 ? BLspeed = 10000 : BLspeed;
				BRspeed > 10000 ? BRspeed = 10000 : BRspeed;
				BLspeed < 0 ? BLspeed = 0 : BLspeed;
				BRspeed < 0 ? BRspeed = 0 : BRspeed;	
		}

			void Speed_monitorAUTO(void)
		{
			pid_update(&BLeft, enc_get_vel(2));
			pid_update(&BRight, enc_get_vel(1));
			SpeedAdjustL = pid_output(&AutoL,7000);
			SpeedAdjustR = pid_output(&AutoR,7000);
			Lspeed += SpeedAdjustL;
			Rspeed += SpeedAdjustR;
				
				Lspeed > 10000 ? Lspeed = 10000 : Lspeed;
				Rspeed > 10000 ? Rspeed = 10000 : Rspeed;
				Lspeed < 0 ? Lspeed = 0 : Lspeed;
				Rspeed < 0 ? Rspeed = 0 : Rspeed;	
		}

