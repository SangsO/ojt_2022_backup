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

#define SCL GPIO_PIN_NO_4
#define SDA GPIO_PIN_NO_5

void delay_btnDeb(void) {
	for (uint32_t i = 0; i < 500000 / 2; i++)
		;
}
/*********************************************************************************************/

I2C_Handle_t I2C1Handle;
//GPIO_Handle_t sclGPIO;
//GPIO_Handle_t sdaGPIO;

//some data
//uint8_t some_data[] = "We are testing I2C master Tx\n"; //Sending Data Value
uint8_t some_data[3] = { 0xAA, 0xFF, 0x55 };
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
//	 * Note : In the below line use GPIO_NO_PUPD option if you want to use external pullup resistors,
//   * then you have to use 3.3K pull up resistors
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

void delay(uint32_t k) {
	uint32_t i;
	for (i = 0; i < k; i++)
		__asm("nop");
}

void reverse_IO(GPIO_Handle_t a) {
	if (a.GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IN) {
		a.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	} else if (a.GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUT) {
		a.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	}
}

void GPIO_ButtonInit(void) {
	GPIO_Handle_t GPIOBtn;

	// User Blue Button gpio configuration
	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBtn);
}

void GPIO_SCL_init(GPIO_Handle_t *temp) {
	//GPIO_Handle_t sclGPIO;
	temp.pGPIOx = GPIOB;
	temp.GPIO_PinConfig.GPIO_PinNumber = SCL;
	temp.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	temp.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	temp.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Init(&temp);

	//GPIO_ToggleOutputPin(GPIOB, 5);
}

GPIO_Handle_t GPIO_SDA_init(void) {
	GPIO_Handle_t sda;

	sda.pGPIOx = GPIOB;
	sda.GPIO_PinConfig.GPIO_PinNumber = SDA;
	sda.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	sda.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	sda.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Init(&sda);

	return sda;
}
/**************************************************************************************************************/
/*							Function Ver.2																	  */
/**************************************************************************************************************/
void i2c_start(void) {
	/*
	 GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, SET);
	 delay(2000);
	 GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, SET);
	 delay(2000);
	 GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, RESET);
	 delay(2000);
	 GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, SET);
	 */
	GPIO_WriteToOutputPin(GPIOB, SDA, RESET);
	delay(300);
	GPIO_WriteToOutputPin(GPIOB, SCL, RESET);
	delay(150);

}
void i2c_stop(void) {
	/*
	 GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, RESET);
	 delay(2000);
	 GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, SET);
	 delay(2000);
	 GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, SET);
	 */
	GPIO_WriteToOutputPin(GPIOB, SDA, SET);
	delay(300);
	GPIO_WriteToOutputPin(GPIOB, SCL, SET);
	delay(150);
}
void check_rwBit(uint8_t rwBit) { //TODO! define rwBit definition
	if (rwBit == 0)
		GPIO_WriteToOutputPin(GPIOB, SDA, RESET);
	else if (rwBit == 1)
		GPIO_WriteToOutputPin(GPIOB, SDA, SET);
	//TODO!!
	GPIO_WriteToOutputPin(GPIOB, SCL, SET);
	delay(300);
	GPIO_WriteToOutputPin(GPIOB, SCL, RESET);

}

void read_ack() {
	reverse_IO(sdaGPIO); //TODO!! Static Global
	delay(300);

	GPIO_WriteToOutputPin(GPIOB, SCL, SET);
	delay(300);
	GPIO_WriteToOutputPin(GPIOB, SCL, RESET);
	delay(300);
	reverse_IO(sdaGPIO);
}

void send(uint8_t data) {
	int idx;
	for (idx = 0; idx < 8; idx++) { //TODO! For Loop Check .. ++ -> -- : if (check)
		if (((data >> (7 - idx)) & 0x1) == 1) {
			GPIO_WriteToOutputPin(GPIOB, SDA, SET);
		} else {
			GPIO_WriteToOutputPin(GPIOB, SDA, SET);
		}
		GPIO_WriteToOutputPin(GPIOB, SCL, SET);
		delay(300);
		GPIO_WriteToOutputPin(GPIOB, SCL, RESET);
		delay(300);
	}
	read_ack();
}
//TODO!! Sending Protocol Function

void send_addr(uint8_t addr) {
	int idx;
	for (idx = 1; idx < 8; idx++) {
		if (((addr >> (7 - idx)) & 0x1) == 1) {
			GPIO_WriteToOutputPin(GPIOB, SDA, SET);
		} else {
			GPIO_WriteToOutputPin(GPIOB, SDA, RESET);
		}
		GPIO_WriteToOutputPin(GPIOB, SCL, SET);
		delay(300);
		GPIO_WriteToOutputPin(GPIOB, SCL, RESET);
		delay(300);
	}
	check_rwBit(0);
	read_ack();
}

void send_data_protocol(uint8_t slave_addr) {
	i2c_start();

	send_addr(slave_addr);
	send(0x41);
	send(0x42);
	send(0x43);

	i2c_stop();
}
/**************************************************************************************************************/

unsigned char i2c_write(unsigned char data) {
	unsigned char idx;

	//write the 8bit data
	for (idx = 0; idx < 8; idx++) {

		delay(2000);

		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, RESET);

		delay(2000);

		if (data & 0x80)
			GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, SET);
		else
			GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, RESET);

		delay(2000);

		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, SET);

		data = data << 1;
	}
	delay(2000);

	//reading ack or nack
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, SET); 	//leave sda high
	reverse_IO(sdaGPIO);						//change the sda direction input

	delay(2000);

	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, SET);	//clock restart

	idx = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_6);	//get ack bit

	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, RESET);
	reverse_IO(sdaGPIO);						//reset the sda direction output

	return idx;

}

unsigned char i2c_read(void) {
	unsigned char idx, data;

	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, RESET);	//sda high
	reverse_IO(sdaGPIO);						//change the sda direction input

	data = 0;
	for (idx = 0; idx < 8; idx++) {

		data = data << 1;

		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, SET);			//clock high

		delay(2000);
		if (GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_6))
			data |= 1;									//get data bit

		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, RESET);			//clock low
		delay(2000);
	}
	reverse_IO(sdaGPIO);						//reset the sda direction output

	//send ack or nack
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, RESET);
	delay(2000);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, SET);

	return data;
}

/*
 int i2c_ack(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
 {
 int ACK = 1;

 reverse_IO(sdaGPIO);

 int temp = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_6);

 reverse_IO(sdaGPIO);

 if(temp != ACK)
 ACK = temp;

 return ACK;
 }
 */
unsigned char i2c_read_nack(void) {
	unsigned char idx, data;

	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, SET);
	reverse_IO(sdaGPIO);

	data = 0;

	for (idx = 0; idx < 8; idx++) {

		data = data << 1;

		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, SET);

		if (GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_6))
			data |= 1;

		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, RESET);

		delay(2000);
	}

	reverse_IO(sdaGPIO);

	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, SET);
	delay(2000);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, SET);

	return data;
}

int main(void) {
	int btn_pr;
	int btn_tim = 0;
	GPIO_Handle_t sdaGPIO;
	GPIO_Handle_t sclGPIO;

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
//		delay(2000);
//		//send some data to the slave
//		I2C_MasterSendData(&I2C1Handle,some_data,strlen((char*)some_data),SLAVE_ADDR,0);
//	}
	/************************************************************************************************/
	//int a = 0; //4byte memory
	//char b; //1byte
	//int *a;
	//char *pb //
	GPIO_ButtonInit();

	//unsigned char input = 0x55;

	/*Set the Idel state*/
	sdaGPIO = GPIO_SDA_init();
	GPIO_SCL_init(&sclGPIO);

	GPIO_WriteToOutputPin(GPIOB, SDA, SET);
	GPIO_WriteToOutputPin(GPIOB, SCL, SET);

	while (1) {

		//while( /*!*/ GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) );
//			delay_btnDeb();
//			//send some data to the slave
//			//GPIO_WriteToOutputPin(GPIOB, 13, 0); //SDA low -> Start bit
//			GPIO_ToggleOutputPin(GPIOB, GPIO_PIN_NO_6);
//			delay(2000);
//			//i2c_send_Byte(0x55);
		//i2c_start();

		//i2c_start();
//
//		i2c_write(SLAVE_ADDR);
//		delay(2000);
//		i2c_write(input);
//		i2c_stop();
		btn_pr = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13);

		if (btn_pr != 0) {
			btn_tim++;
		} else if (btn_pr == 0) {
			send_data_protocol(SLAVE_ADDR);
			btn_pr = 0;
		}
	}

}
/*
 i2c_start();

 i2c_write(SLAVE_ADDR);
 delay(2000);
 i2c_write(input);
 i2c_stop();
 */

//	i2c_start();
//	i2c_write(input);
//	i2c_stop();
