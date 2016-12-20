#include "main.h"
//#include "pid.h"
#include "string.h"

char buffer[128];  
int length;
int Ioutput;
int kP, kI, kD;
int speed[2];
int LeftSpeed, RightSpeed;

void bluetooth_listener(const u8 byte) //u8
{
	if(length == 128)
	{length = 0;}
	buffer[length++] = byte;
	buffer[length] = '\0';
		
	
	if (byte == 'w')  // int value for forward.w
	{
		motor_control(MOTOR1, 0, 50);
		motor_control(MOTOR2, 0, 50);
	}
	if (byte == 's') //s
	{
		motor_control(MOTOR1, 1, 90);
		motor_control(MOTOR2, 1, 90);
	}
	if (byte == 'a') //a
	{
		motor_control(MOTOR1, 1, 50);
		motor_control(MOTOR2, 0, 50); // I think 0 is forward
	}
	if (byte == 'd') //d
	{
		motor_control(MOTOR1, 0, 50);
		motor_control(MOTOR2, 1, 50); // I think 0 is forward
	}
	if (byte == 'k') //k
	{
		motor_control(MOTOR1, 0, 0);
		motor_control(MOTOR2, 0, 0);
	}
	
	
}
	
void bluetooth_init()
{
	uart_init(COM3, 115200);
	uart_interrupt_init(COM3, &bluetooth_listener);
//	int length = 0;
}
/* 
int toInt(char* buffer, int size)
{
	if (size == 1)
	{
		return (int)(buffer[0] - '0');
	}
	else
	{
		return 10 * toInt(buffer, size - 1) + toInt(&buffer[size - 1], 1);
	}
}
*/
/*void RobotControl(Ioutput)
{
	if (Ioutput == 'w')  // int value for forward.w
	{
		motor_control(MOTOR1, 0, 50);
		motor_control(MOTOR2, 0, 50);
	}
	if (Ioutput == 's') //s
	{
		motor_control(MOTOR1, 1, 50);
		motor_control(MOTOR2, 1, 50);
	}
	if (Ioutput == 'a') //a
	{
		motor_control(MOTOR1, 1, 30);
		motor_control(MOTOR2, 0, 30); // I think 0 is forward
	}
	if (Ioutput == 'd') //d
	{
		motor_control(MOTOR1, 0, 30);
		motor_control(MOTOR2, 1, 30); // I think 0 is forward
	}
	if (Ioutput == 'k') //k
	{
		motor_control(MOTOR1, 0, 0);
		motor_control(MOTOR2, 0, 0);
	}
}
*/

int main()
{
	adc_init();
	tft_init(2, WHITE, BLACK);
	ticks_init();
	bluetooth_init();
	motor_init(71,100,0);

	tft_clear();
	
/*	int w = 0;
	int a = 0;
	int s = 0;
	int d = 0;
*/
	//	struct PID *ShooterPID; // declare ShooterPID
	
/*	//ShooterPID specification
	ShooterPID.kp = kP;
	ShooterPID.ki = kI;
	ShooterPID.kd = kD;  */
	
//	pid_init(&ShooterPID, kP, kI, kD);
	
	while(1)
	{	
/*	
		if (ticks_img != get_real_ticks())
		{
			ticks_img = get_real_ticks();
		}
		for (i=0; i<128; i++)
		{
			if(ticks_img % 100 == 0)
			{ 
			Ioutput = toInt(buffer,128);
			tft_prints(0,0,"%d",Ioutput);
			//RobotControl(Ioutput);
			} 
		}
		*/
		tft_clear();
		tft_prints(0,0,"%s", buffer);
	 } 
}
