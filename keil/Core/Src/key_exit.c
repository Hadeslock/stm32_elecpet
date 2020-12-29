/*
 * @Description: 按键中断处理
 * @Author: Hades
 * @Date: 2020-12-11 14:33:54
 * @LastEditors: Hades
 * @LastEditTime: 2020-12-11 14:40:01
 */

#include "key_exit.h"

extern uchar line, colum;

/**
  * @brief  按键中断回调函数
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == KEY1_Pin)
  {
    ClearScreen(BOTH);  //清屏
  }
  else if (GPIO_Pin == KEY2_Pin)
  {
    HAL_Delay(10);
		colum++;
  }
  else if (GPIO_Pin == KEY3_Pin)
  {
    HAL_Delay(10);
		colum--;
  }
  else if (GPIO_Pin == KEY4_Pin)
  {
    HAL_Delay(10);
		line++;
  }
  else if (GPIO_Pin == KEY5_Pin)
  {
    HAL_Delay(10);
		line--;
  }
  
}
