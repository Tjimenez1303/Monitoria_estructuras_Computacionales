/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  //MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  //*********************************************LED2************************************************************************

  //**********************************Paso 0: Cargamos el reloj del puerto A**********************************

  // Cargamos el clock del GPIOA
  RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

  //**********************************Paso 1: Cargamos el moder del puerto A**********************************

  // Cargamos el moder del GPIOA
  uint32_t gpioa_moder = GPIOA->MODER;									// xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx

  //**********************************Paso 2: Limpiamos el moder**********************************************

  // Cargamos una máscara (poner 1) con los bits que quiero limpiar (2 bits)
  uint32_t moder_mask = 0x03;											// 0000 0000 0000 0000 0000 0000 0000 0011

  //Movemos la máscara a las posiciones (bits) del PIN-5
  moder_mask = moder_mask << (2 * 5); 									// 0000 0000 0000 0000 0000 1100 0000 0000

  //Negamos la máscara (~ -> ALTGR + +)
  moder_mask = ~(moder_mask);											// 1111 1111 1111 1111 1111 0011 1111 1111

  //*****************************Paso 3: Juntamos nuestra máscara sin modificar el moder***********************

  //Operacion logica con AND
  gpioa_moder = gpioa_moder & moder_mask;								// xxxx xxxx xxxx xxxx xxxx 00xx xxxx xxxx

  //*****************************Paso 4: Configuramos el PIN 5 como salida (01)********************************

  //Cargamos una máscara con los bits 01
  uint32_t mode_output = 0x01;											// 0000 0000 0000 0000 0000 0000 0000 0001

  //Movemos la máscara a los bits 10 y 11 (PIN 5)
  mode_output = mode_output << (2 * 5);									// 0000 0000 0000 0000 0000 0100 0000 0000

  //*****************************Paso 5: Juntamos nuestra máscara sin modificar el moder***********************

  //Operación lógica OR
  gpioa_moder = gpioa_moder | mode_output;

  //*****************************Paso 6: Escribimos el moder actualizado*****************************************
  GPIOA->MODER = gpioa_moder;


  //*********************************************BOTON (PC13)******************************************************************

   //**********************************Paso 0: Cargamos el reloj del puerto C**********************************

   // Cargamos el clock del GPIOA
   RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

   //**********************************Paso 1: Cargamos el moder del puerto C**********************************

   // Cargamos el moder del GPIOC
   uint32_t gpioc_moder = GPIOC->MODER;									// xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx

   //**********************************Paso 2: Limpiamos el moder**********************************************

   // Cargamos una máscara (poner 1) con los bits que quiero limpiar (2 bits)
   uint32_t moder_mask_button = 0x03;												// 0000 0000 0000 0000 0000 0000 0000 0011

   //Movemos la máscara a las posiciones (bits) del PIN-13
   moder_mask_button = moder_mask_button << (2 * 13); 									// 0000 1100 0000 0000 0000 0000 0000 0000

   //Negamos la máscara (~ -> ALTGR + +)
   moder_mask_button = ~(moder_mask_button);												// 1111 0011 1111 1111 1111 1111 1111 1111

   //*****************************Paso 3: Juntamos nuestra máscara sin modificar el moder***********************

   //Operacion logica con AND
   gpioc_moder = gpioc_moder & moder_mask_button;								// xxxx xxxx xxxx xxxx xxxx 00xx xxxx xxxx

   //*****************************Paso 4: Configuramos el PIN 13 como entrada (00)********************************

   //Cargamos una máscara con los bits 00
   uint32_t mode_output_button = 0x0;												// 0000 0000 0000 0000 0000 0000 0000 0000

   //Movemos la máscara a los bits 10 y 11 (PIN 26)
   mode_output_button = mode_output_button << (2 * 13);									// 0000 0000 0000 0000 0000 0100 0000 0000

   //*****************************Paso 5: Juntamos nuestra máscara sin modificar el moder***********************

   //Operación lógica OR
   gpioc_moder = gpioc_moder | mode_output_button;

  //*****************************Paso 6: Escribimos el moder actualizado*****************************************
  GPIOC->MODER = gpioc_moder;

  uint32_t button_state = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Establecer el bit PA5 en 0;
	  GPIOA->ODR &= ~GPIO_PIN_5;

	  // Leemos el boton
	  button_state = GPIOC->IDR ^= GPIO_PIN_13; //Oprimido = 8192 y NO oprimido = 0

	  if(button_state == 8192)
	  {
		  //GPIOA->ODR ^= GPIO_PIN_5;              // XOR the pin 5 for toggle

		  // Establecer el bit PA5 en 1;
		  GPIOA->ODR |= GPIO_PIN_5;

		  //Agregamos el delay de 100 ms
		  //HAL_Delay(100);

	  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

//static void MX_GPIO_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
///* USER CODE BEGIN MX_GPIO_Init_1 */
///* USER CODE END MX_GPIO_Init_1 */
//
//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOC_CLK_ENABLE();
//  __HAL_RCC_GPIOH_CLK_ENABLE();
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
//
//  /*Configure GPIO pin : B1_Pin */
//  GPIO_InitStruct.Pin = B1_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
//  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : LD2_Pin */
//  GPIO_InitStruct.Pin = LD2_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
//}

/* USER CODE BEGIN 4 */

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
