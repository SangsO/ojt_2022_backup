/*
 * stm32f411xx.h
 *
 *  Created on: Oct 13, 2022
 *      Author: Liam
 */

#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_

#include <stdint.h>
// To now standard int (uint ...)

#define __vo volatile


#define FLASB_BASEADDR			0x08000000U
#define SRAM1_BASEADDR			0x20000000U					//112KB
#define SRAM2_BASEADDR			0x20001C00U
#define ROM_BASEADDR			0x1FFF0000U 				// System Memory Address
#define SRAM					SRAM1_BASEADDR
// main RAM is actually the SRAM1
// So, the SRAM1 is called as main SRAM, that we simply call as SRAM
// Mentioning "U" -> indicating the compiler that this value is not signed, but unsigned

/* AHBx and APBx Bus Peripheral base addresses */

#define PERIPH_BASEADDR				0x4000000U
#define APB1PERIPH_BASEADDR			PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR			0x40010000U

#define AHB1PERIPH_BASEADDR			0x40020000U
#define AHB2PERIPH_BASEADDR			0x50000000U

/* Base Addresses of peripherals which are hanging on AHB1 bus*/

#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR			(AHB1PERIPH_BASEADDR + 0x2000)
#define GPIOJ_BASEADDR			(AHB1PERIPH_BASEADDR + 0x2400)
#define GPIOK_BASEADDR			(AHB1PERIPH_BASEADDR + 0x2800)
#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)

// UART : Cannot work in synchronous mode
// USART : Both OK (synchronous and asynchronous mode)

#define I2C1_BASEADDR			(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR			(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR			(APB1PERIPH_BASEADDR + 0x5000)

#define EXTI_BASEADDR 			(APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400)

/***************************** Peripheral register definition structures *****************************/

// Note : Registers of a peripheral are specific to MCU
// e.g : Numbers of Registers of SPI peripherals of STM32Fx family of MCUs may be different(more or less)
// Compared to number of registers of SPI peripheral of STM32Lx or STm32F0x family of MCUs
// Please check your Device RM

typedef struct
{
	__vo uint32_t MODER;				// Address offset : 0x00
	__vo uint32_t OTYPER;				// Address offset : 0x04
	__vo uint32_t OSPEEDR;				// Address offset :
	__vo uint32_t PUPDR;				// Address offset :
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];			// AFR[0] : GPIO alternate function low register  // Address offset : 0x20 - 0x24

}GPIO_RegDef_t;

typedef struct
{
	__vo uint32_t CR;				// Address offset : 0x00
	__vo uint32_t PLLCFGR;			// Address offset : 0x04
	__vo uint32_t CFGR;				// Address offset : 0x08
	__vo uint32_t CIR;				// Address offset : 0x0C
	__vo uint32_t AHB1RSTR;			// Address offset : 0x10
	__vo uint32_t AHB2RSTR;			// Address offset : 0x14
	__vo uint32_t AHB3RSTR;			// Address offset : 0x18
	uint32_t RESERVED0;				// Reserved, 0x1C
	__vo uint32_t APB1RSTR;			// Address offset : 0x20
	__vo uint32_t APB2RSTR;			// Address offset : 0x24
	uint32_t RESERVED1[2];			// Reserved, 0x28 - 0x2C
	__vo uint32_t AHB1ENR;			// Address offset : 0x30
	__vo uint32_t AHB2ENR;			// Address offset : 0x34
	__vo uint32_t AHB3ENR;			// Address offset : 0x38
	uint32_t RESERVED2;				// Reserved, 0x3C
	__vo uint32_t APB1ENR;			// Address offset : 0x40
	__vo uint32_t APB2ENR;			// Address offset : 0x44
	uint32_t RESERVED3[2] ;			// Reserved, 0x48 - 0x4C
	__vo uint32_t AHB1LPENR;		// Address offset : 0x50
	__vo uint32_t AHB2LPENR;		// Address offset : 0x54
	__vo uint32_t AHB3LPENR;		// Address offset : 0x58
	uint32_t RESERVED4;				// Reserved, 0x5C
	__vo uint32_t APB1LPENR;		// Address offset : 0x60
	__vo uint32_t APB2LPENR;		// Address offset : 0x64
	uint32_t RESERVED5[2];			// Reserved, 0x68 - 0x6C
	__vo uint32_t BDCR;				// Address offset : 0x70
	__vo uint32_t CSR;				// Address offset : 0x74
	uint32_t RESERVED6[2] ;			// Reserved, 0x78 - 0x7C
	__vo uint32_t SSCGR;			// Address offset : 0x80
	__vo uint32_t PLLI2SCFGR;		// Address offset : 0x84


}RCC_RegDef_t;

/* Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t */

#define GPIOA					((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB					((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC					((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD					((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE					((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF					((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG					((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH					((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI					((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ					((GPIO_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK					((GPIO_RegDef_t*)GPIOK_BASEADDR)

#define RCC						((RCC_RegDef_t*)RCC_BASEADDR)

// Clock Enable Macros for GPIOx peripherals
#define GPIOA_PCLK_EN()	(RCC->AHB1ENR |= (1<<0))		//PCLK means Peripheral CloCK // EN means Enable
#define GPIOB_PCLK_EN()	(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()	(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()	(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()	(RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()	(RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()	(RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()	(RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN()	(RCC->AHB1ENR |= (1<<8))
#define GPIOJ_PCLK_EN()	(RCC->AHB1ENR |= (1<<9))
#define GPIOK_PCLK_EN()	(RCC->AHB1ENR |= (1<<10))

// Clock Enable Macros for I2Cx peripherals
#define I2C1_PCLK_EN() (RCC->APB1ENR |= (1<<21))

// Clock Enable Macros for SPIx peripherals
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1<<12))

// Clock Enable Macros for USARTx peripherals

// Clock Enable Macros for SYSCFG peripherals

// Clock Disable Macros for GPIOx peripherals
#define GPIOA_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<0)) 		// [or == |=] set the bit // [and == &= reset the bit
#define GPIOB_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<8))
#define GPIOJ_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<9))
#define GPIOK_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<10))


//Some Generic Macros
#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET


#endif /* INC_STM32F411XX_H_ */
