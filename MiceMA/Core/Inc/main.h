/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SYSLED_Pin GPIO_PIN_13
#define SYSLED_GPIO_Port GPIOC
#define LEYEV_Pin GPIO_PIN_2
#define LEYEV_GPIO_Port GPIOA
#define FEYEV_Pin GPIO_PIN_3
#define FEYEV_GPIO_Port GPIOA
#define REYEV_Pin GPIO_PIN_4
#define REYEV_GPIO_Port GPIOA
#define MOTBAT_Pin GPIO_PIN_5
#define MOTBAT_GPIO_Port GPIOA
#define REYE_Pin GPIO_PIN_14
#define REYE_GPIO_Port GPIOB
#define USRBTN1_Pin GPIO_PIN_8
#define USRBTN1_GPIO_Port GPIOA
#define FEYE_Pin GPIO_PIN_11
#define FEYE_GPIO_Port GPIOA
#define USRBTN2_Pin GPIO_PIN_12
#define USRBTN2_GPIO_Port GPIOA
#define LEYE_Pin GPIO_PIN_5
#define LEYE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
