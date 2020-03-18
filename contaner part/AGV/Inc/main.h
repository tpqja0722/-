/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

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
#define ch_4_Pin GPIO_PIN_13
#define ch_4_GPIO_Port GPIOC
#define ch_5_Pin GPIO_PIN_14
#define ch_5_GPIO_Port GPIOC
#define ch_6_Pin GPIO_PIN_15
#define ch_6_GPIO_Port GPIOC
#define LIMIT_X1_Pin GPIO_PIN_1
#define LIMIT_X1_GPIO_Port GPIOC
#define LIMIT_X2_Pin GPIO_PIN_2
#define LIMIT_X2_GPIO_Port GPIOC
#define LIMIT_Y1_Pin GPIO_PIN_3
#define LIMIT_Y1_GPIO_Port GPIOC
#define M_EN_Pin GPIO_PIN_0
#define M_EN_GPIO_Port GPIOA
#define M1_CLK_Pin GPIO_PIN_4
#define M1_CLK_GPIO_Port GPIOA
#define M1_DIR_Pin GPIO_PIN_5
#define M1_DIR_GPIO_Port GPIOA
#define M2_CLK_Pin GPIO_PIN_6
#define M2_CLK_GPIO_Port GPIOA
#define M2_DIR_Pin GPIO_PIN_7
#define M2_DIR_GPIO_Port GPIOA
#define LIMIT_Y2_Pin GPIO_PIN_4
#define LIMIT_Y2_GPIO_Port GPIOC
#define LIMIT_Z_Pin GPIO_PIN_5
#define LIMIT_Z_GPIO_Port GPIOC
#define M3_EN_Pin GPIO_PIN_0
#define M3_EN_GPIO_Port GPIOB
#define M3_CLK_Pin GPIO_PIN_1
#define M3_CLK_GPIO_Port GPIOB
#define M3_DIR_Pin GPIO_PIN_2
#define M3_DIR_GPIO_Port GPIOB
#define ch_1_Pin GPIO_PIN_10
#define ch_1_GPIO_Port GPIOC
#define ch_2_Pin GPIO_PIN_11
#define ch_2_GPIO_Port GPIOC
#define ch_3_Pin GPIO_PIN_12
#define ch_3_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
