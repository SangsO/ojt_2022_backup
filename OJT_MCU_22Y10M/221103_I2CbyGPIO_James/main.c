/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TEST_DATA 0x22
#define TEST_DATA2 0x24
#define DEVICE_ADDR  0x68
#define SDA_HIGH 1
#define SDA_LOW 0
#define SCL_HIGH 1
#define SCL_LOW 0

#define SDA		(0x1 <<13)
#define SCL 	(0x1 <<15)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t* GPIOB_Out = 0x40020414;
uint32_t* GPIOB_Mode = 0x40020400;
uint32_t* GPIOB_In = 0x40020410;

char data[7] = {0x53, 0x45, 0x4D,0x49, 0x4E, 0x41, 0x52};
char data1 = 0x53;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void nop_delay(uint32_t k)
{
	uint32_t i;
	for(i=0; i<k; i++)
		__asm("nop");
}
void generate_start()
{
	*GPIOB_Out &= ~SDA; // SDA -> 0
	nop_delay(30);
	*GPIOB_Out &= ~SCL; // SCL -> 0
	nop_delay(15);

}

void send_Addr_to_slave()
{
	int i;
	for(i = 1;i <8;i++){
		if(((DEVICE_ADDR >> (7 -i)) & 0x1) == 1){
			*GPIOB_Out |= SDA;
		} else
		{
			*GPIOB_Out &= ~SDA;
		}
		*GPIOB_Out |= SCL; // SCL -> 1
		nop_delay(30);
		*GPIOB_Out &= ~SCL; // SCL -> 0
		nop_delay(30);
	}

	//*GPIOB_Out |= SDA; // SDA -> 1 (SEND)
	*GPIOB_Out &= ~SDA; // 0이 write
	*GPIOB_Out |= SCL; // SCL -> 1
	nop_delay(30);
	*GPIOB_Out &= ~SCL; // SCL -> 0
	*GPIOB_Mode &= ~(0x3 << 26);
	nop_delay(30);

/*
	if(*GPIOB_In & SDA) {
		//ACK
	} else
	{
		//NACK
	}
	*/
	*GPIOB_Out |= SCL; // SCL -> 1
	nop_delay(30);
	*GPIOB_Out &= ~SCL; // SCL -> 0
	nop_delay(30);
	*GPIOB_Mode |= (0x1 << 26);
}

void test_send_data()
{
	int i;
	for(i = 1;i <8;i++){
		if(((TEST_DATA >> (7 -i)) & 0x1) == 1){
			*GPIOB_Out |= SDA;
		} else
		{
			*GPIOB_Out &= ~SDA;
		}
		*GPIOB_Out |= SCL; // SCL -> 1
		nop_delay(30);
		*GPIOB_Out &= ~SCL; // SCL -> 0
		nop_delay(30);
	}

	//*GPIOB_Out |= SDA; // SDA -> 1 (SEND)
	*GPIOB_Out &= ~SDA;
	*GPIOB_Out |= SCL; // SCL -> 1
	nop_delay(30);
	*GPIOB_Out &= ~SCL; // SCL -> 0
	nop_delay(30);
	*GPIOB_Mode &= ~(0x3 << 26);

/*
	if(*GPIOB_In & SDA) {
		//ACK
	} else
	{
		//NACK
	}
	*/
	*GPIOB_Out |= SCL; // SCL -> 1
	nop_delay(30);
	*GPIOB_Out &= ~SCL; // SCL -> 0
	nop_delay(30);
	*GPIOB_Mode |= (0x1 << 26);

}
void test_send_data2()
{
	int i;
	for(i = 1;i <8;i++){
		if(((TEST_DATA2 >> (7 -i)) & 0x1) == 1){
			*GPIOB_Out |= SDA;
		} else
		{
			*GPIOB_Out &= ~SDA;
		}
		*GPIOB_Out |= SCL; // SCL -> 1
		nop_delay(30);
		*GPIOB_Out &= ~SCL; // SCL -> 0
		nop_delay(30);
	}

	//*GPIOB_Out |= SDA; // SDA -> 1 (SEND)
	*GPIOB_Out &= ~SDA;
	*GPIOB_Out |= SCL; // SCL -> 1
	nop_delay(30);
	*GPIOB_Out &= ~SCL; // SCL -> 0
	nop_delay(30);
	*GPIOB_Mode &= ~(0x3 << 26);

/*
	if(*GPIOB_In & SDA) {
		//ACK
	} else
	{
		//NACK
	}
	*/
	*GPIOB_Out |= SCL; // SCL -> 1
	nop_delay(30);
	*GPIOB_Out &= ~SCL; // SCL -> 0
	nop_delay(30);
	*GPIOB_Mode |= (0x1 << 26);
}
void send_data_to_slave(uint32_t single_data)
{
	int i;
	for(i = 0;i<8;i++){
		if(((single_data >> (8-i)) & 0x1) == 1){
			*GPIOB_Out |= SDA;
		} else
		{
			*GPIOB_Out &= ~SDA;
		}
		*GPIOB_Out |= SCL; // SCL -> 1
		nop_delay(30);
		*GPIOB_Out &= ~SCL; // SCL -> 0
		nop_delay(30);
	}
	*GPIOB_Mode &= ~(0x3 << 26);
	if(*GPIOB_In & SDA) {
		//ACK
	} else
	{
		//NACK
	}
	*GPIOB_Out |= SCL; // SCL -> 1
	nop_delay(30);
	*GPIOB_Out &= ~SCL; // SCL -> 0
	nop_delay(30);
	*GPIOB_Mode |= (0x1 << 26);
}

void generate_stop()
{
	*GPIOB_Out |= SDA; // SDA -> 1
	nop_delay(30);
	*GPIOB_Out |= SCL; // SCL -> 1
	nop_delay(15);

}
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  //HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

	*GPIOB_Out |= SDA; // SDA

	*GPIOB_Out |= SCL; // SCL

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 0) {
		  generate_start();
		  send_Addr_to_slave();
		  generate_stop();
		  nop_delay(30);
		  nop_delay(30);
		  generate_start();
		  test_send_data();
		  generate_stop();
		  nop_delay(30);
		  nop_delay(30);
		  nop_delay(30);
		 		  nop_delay(30);
		 		 nop_delay(30);
		 				  nop_delay(30);
		 				 nop_delay(30);
		 						  nop_delay(30);
		 						 nop_delay(30);
		 								  nop_delay(30);
		 								 nop_delay(30);
		 										  nop_delay(30);
		 										 nop_delay(30);
		 												  nop_delay(30);
		 												 nop_delay(30);
		 														  nop_delay(30); nop_delay(30);
		 														  nop_delay(30);
		 														 nop_delay(30);
		 																  nop_delay(30);

		  generate_start();
		  test_send_data2();
		  generate_stop();
		  nop_delay(30);
		  nop_delay(30);
	  }
/*		  for(k = 0; k < 7;k++)
		  {
			  generate_start();
			  send_data_to_slave(data[k]);
			  generate_stop();
			  nop_delay(30);
			  nop_delay(30);
			  nop_delay(30);
		  }

*/
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void I2C_Start() {
	if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 0) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1); // SDA
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1); // SCL
	}
}

void I2C_Send() {

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
