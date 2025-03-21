/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f7xx_hal.h"

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
#define DISP_WR_Pin GPIO_PIN_3
#define DISP_WR_GPIO_Port GPIOJ
#define DISP_RST_Pin GPIO_PIN_12
#define DISP_RST_GPIO_Port GPIOF
#define DISP_CS_Pin GPIO_PIN_13
#define DISP_CS_GPIO_Port GPIOF
#define DISP_DC_Pin GPIO_PIN_14
#define DISP_DC_GPIO_Port GPIOF
#define DISP_RD_Pin GPIO_PIN_15
#define DISP_RD_GPIO_Port GPIOF
#define DISP_D0_Pin GPIO_PIN_0
#define DISP_D0_GPIO_Port GPIOG
#define DISP_D1_Pin GPIO_PIN_1
#define DISP_D1_GPIO_Port GPIOG
#define TOUCH_INT_Pin GPIO_PIN_11
#define TOUCH_INT_GPIO_Port GPIOE
#define TOUCH_INT_EXTI_IRQn EXTI15_10_IRQn
#define TOUCH_SCL_Pin GPIO_PIN_7
#define TOUCH_SCL_GPIO_Port GPIOH
#define TOUCH_SDA_Pin GPIO_PIN_8
#define TOUCH_SDA_GPIO_Port GPIOH
#define DISP_D2_Pin GPIO_PIN_2
#define DISP_D2_GPIO_Port GPIOG
#define DISP_D3_Pin GPIO_PIN_3
#define DISP_D3_GPIO_Port GPIOG
#define DISP_D4_Pin GPIO_PIN_4
#define DISP_D4_GPIO_Port GPIOG
#define DISP_D5_Pin GPIO_PIN_5
#define DISP_D5_GPIO_Port GPIOG
#define DISP_D6_Pin GPIO_PIN_6
#define DISP_D6_GPIO_Port GPIOG
#define DISP_D7_Pin GPIO_PIN_7
#define DISP_D7_GPIO_Port GPIOG
#define DISP_D8_Pin GPIO_PIN_8
#define DISP_D8_GPIO_Port GPIOG
#define DISP_D9_Pin GPIO_PIN_9
#define DISP_D9_GPIO_Port GPIOG
#define DISP_D10_Pin GPIO_PIN_10
#define DISP_D10_GPIO_Port GPIOG
#define DISP_D11_Pin GPIO_PIN_11
#define DISP_D11_GPIO_Port GPIOG
#define DISP_D12_Pin GPIO_PIN_12
#define DISP_D12_GPIO_Port GPIOG
#define DISP_D13_Pin GPIO_PIN_13
#define DISP_D13_GPIO_Port GPIOG
#define DISP_D14_Pin GPIO_PIN_14
#define DISP_D14_GPIO_Port GPIOG
#define DISP_D15_Pin GPIO_PIN_15
#define DISP_D15_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
