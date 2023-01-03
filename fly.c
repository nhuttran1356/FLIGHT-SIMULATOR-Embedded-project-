//	 Trần Minh Nhựt 	19144062
//	 Nguyễn Tiến Phúc	19146137
//	 Ninh Khải Hoàn		19146087
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <wiringSerial.h>

//======================
#define Sample_rate			25
#define Config				26
#define Gryo_config			27
#define Acc_config			28
#define Interrupt			56
#define PWR_managment		107

#define Acc_X 				59
#define Acc_Y				61
#define Acc_Z				63

//========================
int mpu;
float pitch, roll, yaw;

//----------------------------------

void clear_screen();
void read_data_mpu();
void Init_6050();
//-----------------------------------
#define bt1 6
#define bt2 4
#define bt3 5
#define bt4 30
#define bt5 21
#define bt6 22
#define bt7 23
#define bt8 24
#define bt9 25

#define bt10 13
#define bt11 12

int check1 = 1, check2 = 1, check3 = 1, check4 = 1 , check5 = 1, check6 = 1, check7 = 1, check8 = 1, check9 = 1;
int check10, check11;
int motion;

void check_button1(void)
 {
		
	if(digitalRead(bt1)==1)
	check1 = 1;
	else
	check1 = 0;
		
}

void check_button2(void)
 {	
	if(digitalRead(bt2)==1)
	check2 = 1;
	else
	check2 = 0;		
}

void check_button3(void)
 {	
	if(digitalRead(bt3)==1)
	check3 = 1;
	else
	check3 = 0;
		
}

void check_button4(void)
 {
	
	if(digitalRead(bt4)==1)
	check4 = 1;
	else
	check4 = 0;
		
}

void check_button5(void)
 {
	
	if(digitalRead(bt5)==1)
	check5 = 1;
	else
	check5 = 0;
		
}

void check_button6(void)
 {
	
	if(digitalRead(bt6)==1)
	check6 = 1;
	else
	check6 = 0;
		
}

void check_button7(void)
 {
	
	if(digitalRead(bt7)==1)
	check7 = 1;
	else
	check7 = 0;
		
}

void check_button8(void)
 {
	
	if(digitalRead(bt8)==1)
	check8 = 1;
	else
	check8 = 0;
		
}

void check_button9(void)
 {
	
	if(digitalRead(bt9)==1)
	check9 = 1;
	else
	check9 = 0;

}

void check_button10(void)
 {
	if(digitalRead(bt10)==1)
		check10 = 1;
	else
		check10 = 0;

}

void check_button11(void)
 {
	if(digitalRead(bt11)==1)
		check11 = 1;
	else
		check11 = 0;
}


void check_motion()
{
	
	read_data_mpu();		
	if ((pitch>-10 )&& (pitch <10)) motion = 0 ;
	if ((pitch>-40 )&& (pitch <-20)) motion = 1;
	if ((pitch>20 )&& (pitch <60)) motion = 2;
	if (roll<-30) motion = 3;
	if(roll > 20) motion =4 ;
	delay(100);
}

void setup_button()
{
	pinMode(bt1, INPUT);
	pinMode(bt2, INPUT);
	pinMode(bt3, INPUT);
	pinMode(bt4, INPUT);
	pinMode(bt5, INPUT);
	pinMode(bt6, INPUT);
	pinMode(bt7, INPUT);
	pinMode(bt8, INPUT);
	pinMode(bt9, INPUT);
	pinMode(bt10, INPUT);
	pinMode(bt11, INPUT);
	
	wiringPiISR(bt1,INT_EDGE_BOTH,&check_button1);
	wiringPiISR(bt2,INT_EDGE_BOTH,&check_button2);
	wiringPiISR(bt3,INT_EDGE_BOTH,&check_button3);
	wiringPiISR(bt4,INT_EDGE_BOTH,&check_button4);
	wiringPiISR(bt5,INT_EDGE_BOTH,&check_button5);
	wiringPiISR(bt6,INT_EDGE_BOTH,&check_button6);
	wiringPiISR(bt7,INT_EDGE_BOTH,&check_button7);
	wiringPiISR(bt8,INT_EDGE_BOTH,&check_button8);
	wiringPiISR(bt9,INT_EDGE_BOTH,&check_button9);
	wiringPiISR(bt10,INT_EDGE_BOTH,&check_button10);
	wiringPiISR(bt11,INT_EDGE_BOTH,&check_button11);
}

void send_data(int fd)
{
	char data[30] ;	
	sprintf(data,"%d %d %d %d %d %d %d %d %d %d %d %d\r\n",check1, check2, check3, check4,
	check5, check6, check7, check8, check9, check10, check11, motion);		
	serialPrintf(fd,data);
	//printf(data,"%d %d %d %d %d %d %d %d %d %d %d %d\r\n",check1, check2, check3, check4,
	//check5, check6, check7, check8, check9, check10, check11, motion);	
	printf("%d\n", motion);
	delay(100);
}

int main (void)
{
	wiringPiSetup();
	setup_button();
	
	// setup giao tiep I2C
	mpu = wiringPiI2CSetup(0x68);	
	// thiet lap che do cho mpu6050
	Init_6050();
	
	int fd ;
	fd = serialOpen ("/dev/ttyAMA0", 9600);
	wiringPiSetup ();
	printf("serial test begin... \n");	
	
	while (1){

		check_motion();		
		send_data(fd);		
	}
	serialClose(fd) ;
	return 0 ;
}

int16_t read_sensor(unsigned char sensor)
{
	int16_t high, low, data;
	high = wiringPiI2CReadReg8(mpu,sensor); //59
	low = wiringPiI2CReadReg8(mpu,sensor +1); //59+1
	data = (high<<8)|low;
	return data;
}

void Init_6050(void)
{
	// register 25-->28, 56, 107
	
	// sample_rate 500Hz
	wiringPiI2CWriteReg8(mpu,Sample_rate ,15 );
	// khong su dung xung ngoai, tat DLFP
	wiringPiI2CWriteReg8(mpu,Config ,0 );
	// gryo FS: +- 500o/s
	wiringPiI2CWriteReg8(mpu,Gryo_config , 0x08);
	// acc Fs: +-8g
	wiringPiI2CWriteReg8(mpu,Acc_config , 0x10);
	// mo interrupt cua data ready
	wiringPiI2CWriteReg8(mpu,Interrupt , 1);
	// chon nguon xung gryo X
	wiringPiI2CWriteReg8(mpu,PWR_managment , 0x01);
	
}

void read_data_mpu()
{
	float Ax = (float)read_sensor(Acc_X);
	float Ay = (float)read_sensor(Acc_Y);
	float Az = (float)read_sensor(Acc_Z);
	
	pitch = atan2(Ax ,sqrt(pow(Ay,2)+pow(Az,2)))*180/M_PI;
	roll = atan2(Ay ,sqrt(pow(Ax ,2)+pow(Az,2)))*180/M_PI;
	yaw = atan2(Az, sqrt(pow(Ax,2))+(pow(Ay,2)))*180/M_PI;
	printf("pitch = %.5f\n", pitch);
	printf("roll = %.5f\n", roll);
	delay(100);
}



