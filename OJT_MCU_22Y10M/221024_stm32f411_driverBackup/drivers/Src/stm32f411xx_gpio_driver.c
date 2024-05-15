/*
 * stm32f411xx_gpio_driver.c
 *
 *  Created on: Oct 20, 2022
 *      Author: Liam
 */
#include "stm32f411xx_gpio_driver.h"

/**************************************************************************************
 * @fn				-
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			-
 *
 * @Note			-
 */

/**************************************************************************************
 * @fn				- GPIO_PeriClockControl
 *
 * @brief			- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]		- base address of the gpio peripheral
 * @param[in]		- ENABLE or DISABLE macros
 *
 * @return			- None
 *
 * @Note			- None
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi) {
	if (EnorDi == ENABLE) {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_EN();
		} else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_EN();
		} else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_EN();
		} else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_EN();
		} else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_EN();
		} else if (pGPIOx == GPIOF) {
			GPIOF_PCLK_EN();
		} else if (pGPIOx == GPIOG) {
			GPIOG_PCLK_EN();
		} else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_EN();
		} else if (pGPIOx == GPIOI) {
			GPIOI_PCLK_EN();
		} else if (pGPIOx == GPIOJ) {
			GPIOJ_PCLK_EN();
		} else if (pGPIOx == GPIOK) {
			GPIOK_PCLK_EN();
		}
	} else {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_DI();
		} else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_DI();
		} else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_DI();
		} else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_DI();
		} else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_DI();
		} else if (pGPIOx == GPIOF) {
			GPIOF_PCLK_DI();
		} else if (pGPIOx == GPIOG) {
			GPIOG_PCLK_DI();
		} else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_DI();
		} else if (pGPIOx == GPIOI) {
			GPIOI_PCLK_DI();
		} else if (pGPIOx == GPIOJ) {
			GPIOJ_PCLK_DI();
		} else if (pGPIOx == GPIOK) {
			GPIOK_PCLK_DI();
		}
	}
}

/**************************************************************************************
 * @fn				- GPIO_Init
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			-
 *
 * @Note			-
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0; // temp. register

	// 1. configure the mode of gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//the non interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing // value 3 -> 3means binary 11
		pGPIOHandle->pGPIOx->MODER |= temp;

	} else {
		//this part will code later (interrupt mode)
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// 1. configure the FTSR
			EXTI->FTSR |= ( 1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			// Clear the corresponding RTSR bit
			EXTI->RTSR &= ~( 1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// 1. configure the RTSR
			EXTI->RTSR |= ( 1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			// Clear the corresponding FTSR bit
			EXTI->FTSR &= ~( 1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			// 1. configure both FTSR and RTSR
			EXTI->RTSR |= ( 1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->FTSR |= ( 1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

		}

		// 2. configure the GPIO port Selection in SYSCONFIG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /4 ;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber %4 ;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << ( temp2 * 4 );

		// 3. Enable the exti interrupt delivery using IMR
		EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	}

	temp = 0;

	// 2. configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;


	// 3. pull up and pulldown setting
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	// 4. optype
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	// 5. alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		// configure the alt function registers.
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4*temp2) );
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2) );
	}

}
/**************************************************************************************
 * @fn				- GPIO_DeInit
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			-
 *
 * @Note			-
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

		if (pGPIOx == GPIOA) {
			GPIOA_REG_RESET();
		} else if (pGPIOx == GPIOB) {
			GPIOB_REG_RESET();
		} else if (pGPIOx == GPIOC) {
			GPIOC_REG_RESET();
		} else if (pGPIOx == GPIOD) {
			GPIOD_REG_RESET();
		} else if (pGPIOx == GPIOE) {
			GPIOE_REG_RESET();
		} else if (pGPIOx == GPIOF) {
			GPIOF_REG_RESET();
		} else if (pGPIOx == GPIOG) {
			GPIOG_REG_RESET();
		} else if (pGPIOx == GPIOH) {
			GPIOH_REG_RESET();
		} else if (pGPIOx == GPIOI) {
			GPIOI_REG_RESET();
		} else if (pGPIOx == GPIOJ) {
			GPIOJ_REG_RESET();
		} else if (pGPIOx == GPIOK) {
			GPIOK_REG_RESET();
		}
}
/**************************************************************************************
 * @fn				- GPIO_ReadFromInputPin
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			- 0 or 1
 *
 * @Note			-
 */
/**************************************************************************************
 * @fn				- GPIO_ReadFromInputPin
 *
 * @brief			-
 *
 * @param[in]		-
 *
 * @return			-
 *
 * @Note			-
 */
// Data Read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)( (pGPIOx->IDR >> PinNumber) & 0x00000001 ); // IDR value -> I'm shifting by the amount which is mentioned in the PIN number in order to extract
	// that's why I mask all other bit positions with 0. I make every bit position except the least significant
	return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;

	return value;

}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber,uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		//write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= ( 1 << PinNumber );

	}
	else
	{
		//write 0
		pGPIOx->ODR &= ~( 1 << PinNumber );
	}

}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value) //Because there are 16 pins in a port
{
	pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= ( 1<< PinNumber); // XOR operation

}

// IRQ Configuration and ISR handling
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);
