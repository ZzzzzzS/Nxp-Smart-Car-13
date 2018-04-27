#include "include.h"

void delay_IIC( int ms );


//6050初始化程序
uint8_t MPU6050_Inital(void)
{
	delay_IIC( 500 );
	//解除休眠
	I2C_WriteByte(SLAVEADRESS , PWR_MGMT_1 , 0x00 );
	//设置一些寄存器参数，可以查阅头文件中宏定义
	I2C_WriteByte(SLAVEADRESS , SMPLRT_DIV , 0x07 );
	I2C_WriteByte(SLAVEADRESS , CONFIG , 0x06 );
	I2C_WriteByte(SLAVEADRESS , GYRO_CONFIG , 0x18 );
	I2C_WriteByte(SLAVEADRESS , ACCEL_CONFIG , 0x01 );
	//必须再次解除休眠
	I2C_WriteByte(SLAVEADRESS,PWR_MGMT_1,0x00);
	delay_IIC( 100 );
        return I2C_ReadByte(SLAVEADRESS,WHO_AM_I);
}

/*
//获取X轴加速度分量
int getAccX(void)
{
	int AccX = 0;
	char AccXH = 0 , AccXL = 0;

	AccXH = Single_Read_IIC( SLAVEADRESS , ACCEL_XOUT_H );
	AccXL = Single_Read_IIC( SLAVEADRESS , ACCEL_XOUT_L );

	AccX = (AccXH<<8)|AccXL;

	return AccX;
}

//获取Y轴加速度分量
int getAccY(void)
{
	int AccY = 0;
	char AccYH = 0 , AccYL = 0;

	AccYH = Single_Read_IIC( SLAVEADRESS , ACCEL_YOUT_H );
	AccYL = Single_Read_IIC( SLAVEADRESS , ACCEL_YOUT_L );

	AccY = (AccYH<<8)|AccYL;

	return AccY;
}

//获取Z轴加速度分量
int getAccZ(void)
{
	int AccZ = 0;
	char AccZH = 0 , AccZL = 0;

	AccZH = Single_Read_IIC( SLAVEADRESS , ACCEL_ZOUT_H );
	AccZL = Single_Read_IIC( SLAVEADRESS , ACCEL_ZOUT_L );

	AccZ = (AccZH<<8)|AccZL;

	return AccZ;
}

//获得X轴角速度分量
int getGyroX(void)
{
	int GyroX = 0;
	char GyroXH = 0 , GyroXL = 0; 
	
	GyroXH = Single_Read_IIC( SLAVEADRESS , GYRO_XOUT_H );
	GyroXL = Single_Read_IIC( SLAVEADRESS , GYRO_XOUT_L );
	
	GyroX = (GyroXH<<8)|GyroXL;
	
	return GyroX;	
}
//获取Y轴角速度分量
int getGyroY(void)
{
   	int GyroY = 0;
	char GyroYH = 0 , GyroYL = 0; 
	
	GyroYH = Single_Read_IIC( SLAVEADRESS , GYRO_YOUT_H );
	GyroYL = Single_Read_IIC( SLAVEADRESS , GYRO_YOUT_L );
	
	GyroY = (GyroYH<<8)|GyroYL;
	
	return GyroY;	
}
//获取Z轴角速度分量
int getGyroZ(void)
{
   	int GyroZ = 0;
	char GyroZH = 0 , GyroZL = 0; 
	
	GyroZH = Single_Read_IIC( SLAVEADRESS , GYRO_ZOUT_H );
	GyroZL = Single_Read_IIC( SLAVEADRESS , GYRO_ZOUT_L );
	
	GyroZ = (GyroZH<<8)|GyroZL;
	
	return GyroZ;	
}

unsigned int getTemperature(void)
{
 	unsigned int temperature = 0;
	char temperatureH = 0 , temperatureL = 0;

	temperatureH = Single_Read_IIC( SLAVEADRESS , TEMP_OUT_H );
	temperatureL = Single_Read_IIC( SLAVEADRESS , TEMP_OUT_L );

	temperature = (temperatureH<<8)|temperatureL;

	return temperature;
}
*/
//IIC通信中的有效延时
void delay_IIC( int ms )
{
	delay_ms(ms);
}