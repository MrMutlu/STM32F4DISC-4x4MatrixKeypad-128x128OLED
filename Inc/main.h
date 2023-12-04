/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define ROW_2_Pin GPIO_PIN_0
#define ROW_2_GPIO_Port GPIOC
#define ROW_1_Pin GPIO_PIN_1
#define ROW_1_GPIO_Port GPIOC
#define ROW_4_Pin GPIO_PIN_2
#define ROW_4_GPIO_Port GPIOC
#define ROW_3_Pin GPIO_PIN_3
#define ROW_3_GPIO_Port GPIOC
#define COL_2_Pin GPIO_PIN_0
#define COL_2_GPIO_Port GPIOA
#define COL_1_Pin GPIO_PIN_1
#define COL_1_GPIO_Port GPIOA
#define COL_4_Pin GPIO_PIN_2
#define COL_4_GPIO_Port GPIOA
#define COL_3_Pin GPIO_PIN_3
#define COL_3_GPIO_Port GPIOA
#define OLED_RST_Pin GPIO_PIN_11
#define OLED_RST_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_13
#define OLED_CS_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_14
#define OLED_DC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
