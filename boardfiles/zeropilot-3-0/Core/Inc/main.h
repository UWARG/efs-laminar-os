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
#include "stm32l5xx_hal.h"

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
void losInit(void);
void losKernelStart(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO_Interlock_D_Pin GPIO_PIN_2
#define GPIO_Interlock_D_GPIO_Port GPIOF
#define GPIO_Interlock_C_Pin GPIO_PIN_3
#define GPIO_Interlock_C_GPIO_Port GPIOF
#define VBAT_B_SENSE_Pin GPIO_PIN_2
#define VBAT_B_SENSE_GPIO_Port GPIOC
#define PWR_SENSE_Pin GPIO_PIN_4
#define PWR_SENSE_GPIO_Port GPIOA
#define VBAT_A_SENSE_Pin GPIO_PIN_1
#define VBAT_A_SENSE_GPIO_Port GPIOB
#define GPIO_uSD_Detect_Pin GPIO_PIN_11
#define GPIO_uSD_Detect_GPIO_Port GPIOF
#define GPIO_LED_1_Pin GPIO_PIN_0
#define GPIO_LED_1_GPIO_Port GPIOG
#define GPIO_LED_2_Pin GPIO_PIN_1
#define GPIO_LED_2_GPIO_Port GPIOG
#define GPIO_LED_3_Pin GPIO_PIN_2
#define GPIO_LED_3_GPIO_Port GPIOG
#define GPIO_LED_4_Pin GPIO_PIN_3
#define GPIO_LED_4_GPIO_Port GPIOG
#define GPIO_LED_5_Pin GPIO_PIN_4
#define GPIO_LED_5_GPIO_Port GPIOG
#define GPIO_LED_6_Pin GPIO_PIN_5
#define GPIO_LED_6_GPIO_Port GPIOG
#define GPIO_Interlock_B_Pin GPIO_PIN_6
#define GPIO_Interlock_B_GPIO_Port GPIOG
#define GPIO_Interlock_A_Pin GPIO_PIN_7
#define GPIO_Interlock_A_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
