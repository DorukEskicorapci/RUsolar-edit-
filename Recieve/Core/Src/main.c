/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/**
  ******************************************************************************
  * @attention
  * Message from the software team:
  * - For main.c file, DO NOT add code outside of the USER CODE BEGIN - USER CODE END block
  * as it will be overwritten or deleted during code generation.
  ******************************************************************************
  *
*/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can_params.h"
#include "can.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define BOARD_CAN_ID (uint8_t)0x103
#define BOARD_TYPE_ID 0
#define BOARD_TTL 10

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

uint32_t TxMailbox;

can_params_t global_vehicle_parameters;
can_config_t vehicle_can_config;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void gv_commands_callback(uint16_t id, uint32_t value) {

	if (id == global_vehicle_parameters.led.PARAM_ID) {
		HAL_GPIO_WritePin(LED_CAN_GPIO_Port, LED_CAN_Pin, value);
//		HAL_GPIO_TogglePin(LED_CAN_GPIO_Port, LED_CAN_Pin);
		return;
	}

}

void gv_params_callback(uint16_t id, uint32_t value) {
	if (id == global_vehicle_parameters.led.PARAM_ID) {
		HAL_GPIO_WritePin(LED_CAN_GPIO_Port, LED_CAN_Pin, value);
	}
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  // /* MPU Configuration--------------------------------------------------------*/
  // MPU_Config();

  // /* MCU Configuration--------------------------------------------------------*/

  // /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  // HAL_Init();

  // /* USER CODE BEGIN Init */

  // /* USER CODE END Init */

  // /* Configure the system clock */
  // SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  // /* Initialize all configured peripherals */
  // MX_GPIO_Init();
  // MX_CAN1_Init();
  // MX_TIM2_Init();
  // MX_TIM3_Init();
  // /* USER CODE BEGIN 2 */

  // // Start the CAN peripheral
  // HAL_CAN_Start(&hcan1);

  // // Turn on interupt for hcan to receive messages on the buffer
  // HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

  // vehicle_can_config.errors.present = 0;
  // vehicle_can_config.gv_params = &global_vehicle_parameters;
  // vehicle_can_config.can_id = BOARD_CAN_ID;
  // vehicle_can_config.board_type_id = BOARD_TYPE_ID;
  // vehicle_can_config.ttl = BOARD_TTL;
  // sw3_can_init(&hcan1, &vehicle_can_config);
  // sw3_gv_params_init(&global_vehicle_parameters);
  // sw3_can_set_gv_commands_callback(gv_commands_callback);
  // sw3_can_set_gv_params_callback(gv_params_callback);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // Content of the while loop here
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  int BMS_DCH_EN_check = HAL_GPIO_ReadPin(BMS_DCH_EN_GPIO_Port, BMS_DCH_EN_Pin);
    int SW_SCE_check = HAL_GPIO_ReadPin(SW_SCE_GPIO_Port, SW_SCE_PIN);
    int SW_BAT_check = HAL_GPIO_ReadPin(SW_BAT_GPIO_Port, SW_BAT_PIN);
    
    //turn on CON_BAT_G
    if(BMS_DCH_EN_check == 1) { 
      if(SW_BAT_check == 1) {
        HAL_GPIO_WritePin(CON_BAT_G_GPIO_Port, CON_BAT_G_Pin, GPIO_PIN_SET);
      }
      else {
        HAL_GPIO_WritePin(CON_BAT_G_GPIO_Port, CON_BAT_G_Pin, GPIO_PIN_RESET);
      }

      if (SW_SCE_check == 1 && SW_BAT_check == 1) {
        HAL_GPIO_WritePin(CON_SC_G_GPIO_Port, CON_SC_G_Pin, GPIO_PIN_SET);
      } else {
        HAL_GPIO_WritePin(CON_SC_G_GPIO_Port, CON_SC_G_Pin, GPIO_PIN_RESET);
      }      

      
    } else {
      HAL_GPIO_WritePin(CON_BAT_G_GPIO_Port, CON_BAT_G_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(CON_SC_G_GPIO_Port, CON_SC_G_Pin, GPIO_PIN_RESET);
    }
	  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

    //sw3_can_loop();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
// void SystemClock_Config(void)
// {
//   RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

//   /** Configure the main internal regulator output voltage
//   */
//   __HAL_RCC_PWR_CLK_ENABLE();
//   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

//   /** Initializes the RCC Oscillators according to the specified parameters
//   * in the RCC_OscInitTypeDef structure.
//   */
//   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//   RCC_OscInitStruct.PLL.PLLM = 4;
//   RCC_OscInitStruct.PLL.PLLN = 96;
//   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
//   RCC_OscInitStruct.PLL.PLLQ = 2;
//   RCC_OscInitStruct.PLL.PLLR = 2;
//   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   /** Initializes the CPU, AHB and APB buses clocks
//   */
//   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                               |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
//   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

//   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
//   {
//     Error_Handler();
//   }
// }

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  // /* USER CODE BEGIN CAN1_Init 0 */

  // /* USER CODE END CAN1_Init 0 */

  // /* USER CODE BEGIN CAN1_Init 1 */

  // /* USER CODE END CAN1_Init 1 */
  // hcan1.Instance = CAN1;
  // hcan1.Init.Prescaler = 8;
  // hcan1.Init.Mode = CAN_MODE_NORMAL;
  // hcan1.Init.SyncJumpWidth = CAN_SJW_2TQ;
  // hcan1.Init.TimeSeg1 = CAN_BS1_2TQ;
  // hcan1.Init.TimeSeg2 = CAN_BS2_3TQ;
  // hcan1.Init.TimeTriggeredMode = DISABLE;
  // hcan1.Init.AutoBusOff = DISABLE;
  // hcan1.Init.AutoWakeUp = DISABLE;
  // hcan1.Init.AutoRetransmission = DISABLE;
  // hcan1.Init.ReceiveFifoLocked = DISABLE;
  // hcan1.Init.TransmitFifoPriority = DISABLE;
  // if (HAL_CAN_Init(&hcan1) != HAL_OK)
  // {
  //   Error_Handler();
  // }
  // /* USER CODE BEGIN CAN1_Init 2 */
  // CAN_FilterTypeDef canfilterconfig;

  // canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
  // canfilterconfig.FilterBank = 18;  // which filter bank to use from the assigned ones
  // canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  // canfilterconfig.FilterIdHigh = 0x000<<5; // 0x001
  // canfilterconfig.FilterIdLow = 0;
  // canfilterconfig.FilterMaskIdHigh = 0x000<<5; // 0x001
  // canfilterconfig.FilterMaskIdLow = 0x0000;
  // canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
  // canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
  // canfilterconfig.SlaveStartFilterBank = 20;  // how many filters to assign to the CAN1 (master can)

  // HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
  // /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  // /* USER CODE BEGIN TIM2_Init 0 */

  // /* USER CODE END TIM2_Init 0 */

  // TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  // TIM_MasterConfigTypeDef sMasterConfig = {0};

  // /* USER CODE BEGIN TIM2_Init 1 */

  // /* USER CODE END TIM2_Init 1 */
  // htim2.Instance = TIM2;
  // htim2.Init.Prescaler = 24;
  // htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  // htim2.Init.Period = 1000000;
  // htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  // htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  // if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  // {
  //   Error_Handler();
  // }
  // sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  // if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  // {
  //   Error_Handler();
  // }
  // sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  // sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  // if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  // {
  //   Error_Handler();
  // }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  // /* USER CODE BEGIN TIM3_Init 0 */

  // /* USER CODE END TIM3_Init 0 */

  // TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  // TIM_MasterConfigTypeDef sMasterConfig = {0};

  // /* USER CODE BEGIN TIM3_Init 1 */

  // /* USER CODE END TIM3_Init 1 */
  // htim3.Instance = TIM3;
  // htim3.Init.Prescaler = 24000;
  // htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  // htim3.Init.Period = 100;
  // htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  // htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  // if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  // {
  //   Error_Handler();
  // }
  // sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  // if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  // {
  //   Error_Handler();
  // }
  // sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  // sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  // if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  // {
  //   Error_Handler();
  // }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

// /**
//   * @brief GPIO Initialization Function
//   * @param None
//   * @retval None
//   */
 static void MX_GPIO_Init(void)
{
//   GPIO_InitTypeDef GPIO_InitStruct = {0};
// /* USER CODE BEGIN MX_GPIO_Init_1 */
// /* USER CODE END MX_GPIO_Init_1 */

//   /* GPIO Ports Clock Enable */
//   __HAL_RCC_GPIOE_CLK_ENABLE();
//   __HAL_RCC_GPIOC_CLK_ENABLE();
//   __HAL_RCC_GPIOF_CLK_ENABLE();
//   __HAL_RCC_GPIOH_CLK_ENABLE();
//   __HAL_RCC_GPIOA_CLK_ENABLE();
//   __HAL_RCC_GPIOG_CLK_ENABLE();
//   __HAL_RCC_GPIOD_CLK_ENABLE();

//   /*Configure GPIO pin Output Level */
//   HAL_GPIO_WritePin(GPIOE, CON_BAT_G_Pin|CON_SC_G_Pin, GPIO_PIN_RESET);

//   /*Configure GPIO pin Output Level */
//   HAL_GPIO_WritePin(GPIOF, LED_CAN_Pin|LED_BOARD_Pin, GPIO_PIN_RESET);

//   /*Configure GPIO pins : CON_BAT_G_Pin CON_SC_G_Pin */
//   GPIO_InitStruct.Pin = CON_BAT_G_Pin|CON_SC_G_Pin;
//   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//   HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

//   /*Configure GPIO pin : BTN_1_Pin */
//   GPIO_InitStruct.Pin = BTN_1_Pin;
//   GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//   GPIO_InitStruct.Pull = GPIO_PULLUP;
//   HAL_GPIO_Init(BTN_1_GPIO_Port, &GPIO_InitStruct);

//   /*Configure GPIO pins : LED_CAN_Pin LED_BOARD_Pin */
//   GPIO_InitStruct.Pin = LED_CAN_Pin|LED_BOARD_Pin;
//   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//   HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

//   /*Configure GPIO pin : BMS_DCH_EN_Pin */
//   GPIO_InitStruct.Pin = BMS_DCH_EN_Pin;
//   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   HAL_GPIO_Init(BMS_DCH_EN_GPIO_Port, &GPIO_InitStruct);

//   /*Configure GPIO pin : SW_SCE_Pin */
//   GPIO_InitStruct.Pin = SW_SCE_Pin;
//   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   HAL_GPIO_Init(SW_SCE_GPIO_Port, &GPIO_InitStruct);

//   /*Configure GPIO pin : SW_BAT_Pin */
//   GPIO_InitStruct.Pin = SW_BAT_Pin;
//   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   HAL_GPIO_Init(SW_BAT_GPIO_Port, &GPIO_InitStruct);

//   /* EXTI interrupt init*/
//   HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
//   HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  // /** Initializes and configures the Region and the memory to be protected
  // */
  // MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  // MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  // MPU_InitStruct.BaseAddress = 0x0;
  // MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  // MPU_InitStruct.SubRegionDisable = 0x87;
  // MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  // MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  // MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  // MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  // MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  // MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  // HAL_MPU_ConfigRegion(&MPU_InitStruct);
  // /* Enables the MPU */
  // HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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
