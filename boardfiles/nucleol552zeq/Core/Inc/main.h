/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"

#include "stm32l5xx_ll_ucpd.h"
#include "stm32l5xx_ll_bus.h"
#include "stm32l5xx_ll_cortex.h"
#include "stm32l5xx_ll_rcc.h"
#include "stm32l5xx_ll_system.h"
#include "stm32l5xx_ll_utils.h"
#include "stm32l5xx_ll_pwr.h"
#include "stm32l5xx_ll_gpio.h"
#include "stm32l5xx_ll_dma.h"

#include "stm32l5xx_ll_exti.h"

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
#define PWM1_Pin GPIO_PIN_3
#define PWM1_GPIO_Port GPIOE
#define PWM2_Pin GPIO_PIN_4
#define PWM2_GPIO_Port GPIOE
#define PWM3_Pin GPIO_PIN_5
#define PWM3_GPIO_Port GPIOE
#define PWM4_Pin GPIO_PIN_6
#define PWM4_GPIO_Port GPIOE
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define MS4525DO_SDA_Pin GPIO_PIN_0
#define MS4525DO_SDA_GPIO_Port GPIOF
#define MS4525DO_SCL_Pin GPIO_PIN_1
#define MS4525DO_SCL_GPIO_Port GPIOF
#define DSHOT5_Pin GPIO_PIN_0
#define DSHOT5_GPIO_Port GPIOA
#define VN300_RX_Pin GPIO_PIN_3
#define VN300_RX_GPIO_Port GPIOA
#define NEOM8_NSS_Pin GPIO_PIN_0
#define NEOM8_NSS_GPIO_Port GPIOB
#define DSHOT1_Pin GPIO_PIN_9
#define DSHOT1_GPIO_Port GPIOE
#define DSHOT2_Pin GPIO_PIN_11
#define DSHOT2_GPIO_Port GPIOE
#define DSHOT3_Pin GPIO_PIN_13
#define DSHOT3_GPIO_Port GPIOE
#define DSHOT4_Pin GPIO_PIN_14
#define DSHOT4_GPIO_Port GPIOE
#define NEOM8_MOSI_Pin GPIO_PIN_15
#define NEOM8_MOSI_GPIO_Port GPIOE
#define JETSON_TX_Pin GPIO_PIN_10
#define JETSON_TX_GPIO_Port GPIOB
#define UCPD_FLT_Pin GPIO_PIN_14
#define UCPD_FLT_GPIO_Port GPIOB
#define JETSON_RX_Pin GPIO_PIN_9
#define JETSON_RX_GPIO_Port GPIOD
#define PPM_IN1_Pin GPIO_PIN_12
#define PPM_IN1_GPIO_Port GPIOD
#define PPM_IN2_Pin GPIO_PIN_13
#define PPM_IN2_GPIO_Port GPIOD
#define PPM_IN3_Pin GPIO_PIN_14
#define PPM_IN3_GPIO_Port GPIOD
#define NEOM8_SCK_Pin GPIO_PIN_2
#define NEOM8_SCK_GPIO_Port GPIOG
#define NEOM8_MISO_Pin GPIO_PIN_3
#define NEOM8_MISO_GPIO_Port GPIOG
#define ST_LINK_VCP_TX_Pin GPIO_PIN_7
#define ST_LINK_VCP_TX_GPIO_Port GPIOG
#define ST_LINK_VCP_RX_Pin GPIO_PIN_8
#define ST_LINK_VCP_RX_GPIO_Port GPIOG
#define LED_GREEN_Pin GPIO_PIN_7
#define LED_GREEN_GPIO_Port GPIOC
#define RFD900_RX_Pin GPIO_PIN_10
#define RFD900_RX_GPIO_Port GPIOA
#define MATEKSYS3901_TX_Pin GPIO_PIN_10
#define MATEKSYS3901_TX_GPIO_Port GPIOC
#define MATEKSYS3901_RX_Pin GPIO_PIN_11
#define MATEKSYS3901_RX_GPIO_Port GPIOC
#define VN300_TX_Pin GPIO_PIN_5
#define VN300_TX_GPIO_Port GPIOD
#define UCPD_DBN_Pin GPIO_PIN_5
#define UCPD_DBN_GPIO_Port GPIOB
#define RFD900_TX_Pin GPIO_PIN_6
#define RFD900_TX_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_7
#define LED_BLUE_GPIO_Port GPIOB
#define BMX_160_SCL_Pin GPIO_PIN_8
#define BMX_160_SCL_GPIO_Port GPIOB
#define BMX_160_SDA_Pin GPIO_PIN_9
#define BMX_160_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
