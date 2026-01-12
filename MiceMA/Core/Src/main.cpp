/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <OneButton.h>

#include <Mouse.h>
#include <BrainConfig.h>
#include <BodyConfig.h>

#include <BabyMouse.h>
#include <YoungMouse.h>
#include <YoungAdultMouse.h>
#include <AdultMouse.h>
#include <OldMouse.h>


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

Simulation mySimulation;

#if SIMULATION == 1
BabyMouse   BDavid ( &mySimulation );
YoungMouse  YDavid ( &mySimulation );
YoungAdultMouse   NDavid ( &mySimulation );
AdultMouse  ADavid ( &mySimulation );
OldMouse    ODavid ( &mySimulation );
#else
BabyMouse   BDavid ( NULL );
YoungMouse  YDavid ( NULL );
YoungAdultMouse    NDavid ( NULL );
AdultMouse  ADavid ( NULL );
OldMouse    ODavid ( NULL );
#endif

// Active mouse
//BabyMouse      *mice =  &BDavid;
//YoungMouse     *mice =  &YDavid;
AdultMouse     *mice =  &ADavid;
//OldMouse       *mice =  &ODavid;
//YoungAdultMouse  *mice =  &NDavid;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void click1() {

	ssd1306_clearScreen();
	ssd1306_printFixedN(0,16,"WALKING   ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	mice->WalkToGoal( );
#else
	mice->objBody.start_motor_controllers();
	mice->WalkToGoal( );
	mice->objBody.reset_motor_controllers();
#endif
	ssd1306_clearScreen();

} // click1

void click2() {

	ssd1306_clearScreen();
	ssd1306_printFixedN(0,16,"RUNNING   ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	mice->RunToGoal( );
#else
	mice->objBody.start_motor_controllers();
	mice->RunToGoal( );
	mice->objBody.reset_motor_controllers();
#endif
	ssd1306_clearScreen();

} // click2


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
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM9_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  cycleCounterInit();

  OneButton  button1, button2;


	ssd1306_setFixedFont(ssd1306xled_font6x8);
	ssd1306_128x64_i2c_init();
	ssd1306_clearScreen();

	button1.Init(USRBTN1_GPIO_Port, USRBTN1_Pin, true); //, true);
	button1.attachClick(click1);

	button2.Init(USRBTN2_GPIO_Port, USRBTN2_Pin, true); //, true);
	button2.attachClick(click2);

	mice->miceReset();

	/* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

  	  button1.tick();
  	  button2.tick();

  	  mice->objBody.BodyDisplay();

	  HAL_GPIO_TogglePin(SYSLED_GPIO_Port, SYSLED_Pin);
	  HAL_Delay(500); //delay 100ms

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim == &htim9) {
		mice->miceUpdate();
	}

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
	   	HAL_GPIO_TogglePin(SYSLED_GPIO_Port, SYSLED_Pin);
	    HAL_Delay(200); //delay 200ms
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
