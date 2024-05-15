/*
 * stm32f407xx_rcc_driver.h
 *
 *  Created on: Mar 29, 2019
 *      Author: admin
 */

#ifndef INC_STM32F411XX_RCC_DRIVER_H_
#define INC_STM32F411XX_RCC_DRIVER_H_

#include <stm32f411xx.h>

/*  System clock switch status */
#define HSI		0x00
#define HSE		0x01
#define PLL		0x10
#define NO_APP	0x11

/* Frequency of System clock(MHz) */
#define HSI_FREQ	16
#define HSE_FREQ	8



//This returns the APB1 clock value
uint32_t RCC_GetPCLK1Value(void);

//This returns the APB2 clock value
uint32_t RCC_GetPCLK2Value(void);


uint32_t  RCC_GetPLLOutputClock(void);
#endif /* INC_STM32F411XX_RCC_DRIVER_H_ */
