/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
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
#include "dma.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
DMA_HandleTypeDef hdma_dma_generator0;
DMA_HandleTypeDef hdma_dma_generator1;

/**
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_dma_generator0
  *   hdma_dma_generator1
  */
void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_dma_generator0 on DMA1_Channel1 */
  hdma_dma_generator0.Instance = DMA1_Channel1;
  hdma_dma_generator0.Init.Request = DMA_REQUEST_GENERATOR0;
  hdma_dma_generator0.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_dma_generator0.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_dma_generator0.Init.MemInc = DMA_MINC_ENABLE;
  hdma_dma_generator0.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_dma_generator0.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_dma_generator0.Init.Mode = DMA_NORMAL;
  hdma_dma_generator0.Init.Priority = DMA_PRIORITY_LOW;
  if (HAL_DMA_Init(&hdma_dma_generator0) != HAL_OK)
  {
    Error_Handler();
  }

  /*  */
  if (HAL_DMA_ConfigChannelAttributes(&hdma_dma_generator0, DMA_CHANNEL_NPRIV) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure DMA request hdma_dma_generator1 on DMA1_Channel2 */
  hdma_dma_generator1.Instance = DMA1_Channel2;
  hdma_dma_generator1.Init.Request = DMA_REQUEST_GENERATOR1;
  hdma_dma_generator1.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_dma_generator1.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_dma_generator1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_dma_generator1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_dma_generator1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_dma_generator1.Init.Mode = DMA_NORMAL;
  hdma_dma_generator1.Init.Priority = DMA_PRIORITY_LOW;
  if (HAL_DMA_Init(&hdma_dma_generator1) != HAL_OK)
  {
    Error_Handler();
  }

  /*  */
  if (HAL_DMA_ConfigChannelAttributes(&hdma_dma_generator1, DMA_CHANNEL_NPRIV) != HAL_OK)
  {
    Error_Handler();
  }

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

