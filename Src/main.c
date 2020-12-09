
#include "main.h"
#include "lcd12864.h"
#include "stm32f1xx_hal.h"
#include "word_lib.h"
//#include "stm32f1xx_hal_gpio.h"

//static void MX_TIM1_Init(void);

TIM_HandleTypeDef htim1;

int main(void)
{
	uchar i,line,colum;
	uchar *address ;
	uchar en_word_width=8, en_word_height=16;
	
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
  
	while (1)
	{ 
		
		line = 1;				
		colum = 1;			
		address = hzk;		
		SetOnOff(1);		

		for(i=0;i<8;i++)	
		{
			LCDShowEnglishWord(line,colum,address);
			address += 16;
			colum += en_word_width;
		}	
		
		HAL_Delay(3000);	//延时
	}

}

/**
 * @description: 系统时钟配置
 * @param {*}
 * @return {*}
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	/**Initializes the CPU, AHB and APB busses clocks*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	Error_Handler();
	}

	/**Initializes the CPU, AHB and APB busses clocks*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
	Error_Handler();
	}

	/**Configure the Systick interrupt time */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	/**Configure the Systick */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
 * @description: 定时器初始化
 * @param {*}
 * @return {*}
 */
//static void MX_TIM1_Init(void)
//{
//	TIM_ClockConfigTypeDef sClockSourceConfig;
//	TIM_MasterConfigTypeDef sMasterConfig;

//	htim1.Instance = TIM1;
//	htim1.Init.Prescaler = 0;
//	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
//	htim1.Init.Period = 0;
//	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//	htim1.Init.RepetitionCounter = 0;
//	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
//	{
//	Error_Handler();
//	}

//	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
//	{
//	Error_Handler();
//	}

//	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
//	{
//	Error_Handler();
//	}

//}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif



