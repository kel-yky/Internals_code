#include "encoder.h"
#include "main.h"
#include "pid.h" 

int kP1 = 10;
int kI1 = 5;
int kD1 = 10;
int kP2 = 10;
int kI2 = 5;
int kD2 = 10;
int SpeedAdjustL = 0;
int SpeedAdjustR = 0;
int motor1;
int motor2;
	
void Speed_monitor(void);

struct PID *Left; // declare ShooterPID for left motor
struct PID *Right; // declare ShooterPID for right motor

void Speed_monitor(void); //function prototype

int motor1;
int motor2;
int Lspeed = 30;
int Rspeed = 30;  //right motor very slow
int idealSpeed;


int main()
{
//0 is forward, 1 is backward
encoder_init();
motor_init(71,100,0);
pneumatic_init();
tft_init(2, WHITE, BLACK);
//pid_init(Left, kP1, kI1, kD1);
//pid_init(Right, kP2, kI2, kD2);
int stage = 0;


while(1)
{
	encoder_update();
	motor1 = encoder_count(1);   //number of turns by motor 1 <- not defined
	motor2 = encoder_count(2);   //number of turns by motor 2 <- not defined

			idealSpeed = 80;
			Speed_monitor();
			motor1 = encoder_count(1);   //number of turns by motor 1 <- not defined
			motor2 = encoder_count(2);   //number of turns by motor 2 <- not defined
			motor_control(MOTOR1, 0, Lspeed);   //update motor speed
			motor_control(MOTOR2, 0, Rspeed);			//this should be 20 when rotation less than 1 so should initiate motor?
			tft_clear();
			tft_prints(0,0, "stage %d %d", stage, motor1);
			tft_prints(0,20, "stage %d %d", stage, motor2);
		/*}
		else
		{
			motor_control(MOTOR1, 0, 0);
			motor_control(MOTOR2, 0, 0);
			stage++;
		}
	} */
}
}

	void Speed_monitor(void)
		{
			pid_update(Left, enc_get_vel(1));
			pid_update(Right, enc_get_vel(2));
			SpeedAdjustL = pid_output(Left,idealSpeed);
			SpeedAdjustR = pid_output(Right,idealSpeed);
				
				Lspeed > 100 ? Lspeed = 100 : Lspeed;
				Rspeed > 100 ? Rspeed = 100 : Rspeed;
				Lspeed < 0 ? Lspeed = 0 : Lspeed;
				Rspeed < 0 ? Rspeed = 0 : Rspeed;
				
		}