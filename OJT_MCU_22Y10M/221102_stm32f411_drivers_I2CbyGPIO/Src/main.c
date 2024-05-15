/*
 * 010i2c_master_tx_testing.c
 *
 *  Created on: Feb 24, 2019
 *      Author: admin
 */


#include<stdio.h>
#include <stm32f407xx_old.h>
#include<string.h>

#define MY_ADDR 0x61;
#define SLAVE_ADDR  0x68

void delay_btnDeb(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}
/*********************************************************************************************/

I2C_Handle_t I2C1Handle;
GPIO_Handle_t sclGPIO;
GPIO_Handle_t sdaGPIO;


//some data
//uint8_t some_data[] = "We are testing I2C master Tx\n"; //Sending Data Value
uint8_t some_data[3] = {0xAA, 0xFF, 0x55};
uint8_t send_data = 0x55;

/*
 * PB6-> SCL
 * PB9 or PB7 -> SDA
 */



//void I2C1_GPIOInits(void)
//{
//	GPIO_Handle_t I2CPins;
//
//	/*Note : Internal pull-up resistors are used ... My case : Not use, External Pull-up*/
//
//	//struct . and -> difference?? :
//
//	I2CPins.pGPIOx = GPIOB; // Using the GPIO Port
//	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;		// choose alternative function mode
//	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;	// choose open-drain mode
//	/*
//	 * Note : In the below line use GPIO_NO_PUPD option if you want to use external pullup resistors, then you have to use 3.3K pull up resistors
//	 * for both SDA and SCL lines
//	 */
//	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;	// Not Need... Because I Set the Outside Pullup Circuit -> GPIO_NO_PUPD
//	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
//	I2CPins. GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//
//	//scl
//	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;		// SCL line
//	GPIO_Init(&I2CPins);
//
//
//	//sda
//	//Note : since we found a glitch on PB9 , you can also try with PB7
//	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;		// SDA line
//
//	GPIO_Init(&I2CPins);
//
//}
//
//void I2C1_Inits(void)
//{
//	I2C1Handle.pI2Cx = I2C1;
//	I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;	// ACK Enable
//	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;		// Fix my Address
//	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
//	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
//
//	I2C_Init(&I2C1Handle);
//}


/************************************************************************************************/

void delay(uint32_t k)
{
    uint32_t i;
    for(i=0; i<k; i++)
        __asm("nop");
}

void reverse_IO(GPIO_Handle_t a)
{
	if(a.GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IN)
	{
		a.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	}
	else if (a.GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUT)
	{
		a.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	}
}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	// User Blue Button gpio configuration
	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBtn);
}

void GPIO_SCL_init(void)
{
	GPIO_Handle_t sclGPIO;

	sclGPIO.pGPIOx = GPIOA;
	sclGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	sclGPIO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	sclGPIO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	sclGPIO.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&sclGPIO);

	//GPIO_ToggleOutputPin(GPIOA, 5);
}

void GPIO_SDA_init(void)
{
	GPIO_Handle_t sdaGPIO;

	sdaGPIO.pGPIOx = GPIOA;
	sdaGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	sdaGPIO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	sdaGPIO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	sdaGPIO.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&sdaGPIO);
}

void i2c_start(void)
{
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, SET);
	delay(30);
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, SET);
	delay(30);

	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, RESET);
	delay(30);
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, RESET);
	delay(30);
}

void i2c_stop(void)
{
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, RESET);
	delay(30);
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, SET);
	delay(30);
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, SET);
	delay(30);
}

unsigned char i2c_write(unsigned char data)
{
	unsigned char idx;

	//write the 8bit data
	for (idx = 0; idx < 8; idx++) {

		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, RESET);

		if(data & 0x80)
			GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, SET);
		else
			GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, RESET);

		data = data << 1;
	}

	//reading ack or nack
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, SET); 	//leave sda high
	reverse_IO(sdaGPIO);								//change the sda direction input

	delay(30);

	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, SET);	//clock restart

	idx = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_6);	//get ack bit

	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, RESET);
	reverse_IO(sdaGPIO);								//reset the sda direction output

	return idx;

}

unsigned char i2c_read(void)
{
	unsigned char idx, data;

	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, RESET);	//sda high
	reverse_IO(sdaGPIO);								//change the sda direction input

	data = 0;
	for(idx = 0; idx < 8; idx++){

		data = data << 1;

		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, SET);//clock high

		delay(30);
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_6))
			data |= 1;									//get data bit

		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, RESET);//clock low
		delay(30);
	}
	reverse_IO(sdaGPIO);								//reset the sda direction output

	//send ack or nack
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, RESET);
	delay(30);
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, SET);

	return data;
}
/*
int i2c_ack(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	int ACK = 1;

	reverse_IO(sdaGPIO);

	int temp = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_6);

	reverse_IO(sdaGPIO);

	if(temp != ACK)
		ACK = temp;

	return ACK;
}
*/
unsigned char i2c_read_nack(void)
{
	unsigned char idx, data;

	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, SET);
	reverse_IO(sdaGPIO);

	data = 0;

	for(idx = 0; idx < 8; idx ++) {

		data = data << 1;

		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, SET);

		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_6))
			data |= 1;

		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, RESET);

		delay(30);
	}

	reverse_IO(sdaGPIO);

	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, SET);
	delay(30);
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, SET);

	return data;
}

int main(void)
{

	/*********************************************************************************************/
//	GPIO_ButtonInit();
//	//i2c pin inits
//	//I2C1_GPIOInits();
//	//i2c peripheral configuration
//	//I2C1_Inits();
//	//enable the i2c peripheral
//	//I2C_PeripheralControl(I2C1,ENABLE);
//
//	while(1)
//	{
//		//wait till button is pressed
//		while( /*!*/ GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) );
//		//to avoid button de-bouncing related issues 200ms of delay
//		delay(30);
//		//send some data to the slave
//		I2C_MasterSendData(&I2C1Handle,some_data,strlen((char*)some_data),SLAVE_ADDR,0);
//	}
	/************************************************************************************************/
	//GPIO_ButonInit();

	unsigned char input = 0x55;

	/*Set the Idel state*/
	GPIO_SCL_init();
	GPIO_SDA_init();

	while(1)
		{

			//while( /*!*/ GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) );
//			delay_btnDeb();
//			//send some data to the slave
//			//GPIO_WriteToOutputPin(GPIOA, 13, 0); //SDA low -> Start bit
//			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_6);
//			delay(30);
//			//i2c_send_Byte(0x55);
			//i2c_start();
			i2c_write(SLAVE_ADDR);
			i2c_stop();

			i2c_start();
			i2c_write(input);
			i2c_stop();

		}

	i2c_start();
	i2c_write(SLAVE_ADDR);
	i2c_stop();

//	i2c_start();
//	i2c_write(input);
//	i2c_stop();



}
