/*
 * @Description: 
 * @Author: Hades
 * @Date: 2020-12-02 13:10:45
 * @LastEditors: Hades
 * @LastEditTime: 2020-12-09 16:12:20
 */

#ifndef _LCD12864_H
#define _LCD12864_H

#include "main.h"

#define ON 1
#define OFF 0

#define LEFT 0
#define RIGHT 1
#define BOTH 2

#define     DATABUS     	GPIOB
#define     DATA        	GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7

#define     CS1         	GPIO_PIN_3      //左屏幕选择，低电平有效
#define     RESET_CS1       GPIO_SetBits(GPIOC,   CS1)
#define     SET_CS1       	GPIO_ResetBits(GPIOC, CS1)

#define     CS2         	GPIO_PIN_4      //右屏幕选择，低电平有效
#define     RESET_CS2       GPIO_SetBits(GPIOC,   CS2)
#define     SET_CS2       	GPIO_ResetBits(GPIOC, CS2)

#define     E           	GPIO_PIN_5      //指令数据控制
#define     E_H       		GPIO_SetBits(GPIOC,   E)
#define     E_L       		GPIO_ResetBits(GPIOC, E)

#define   	RW          	GPIO_PIN_6      //读写控制
#define     RW_Read      	GPIO_SetBits(GPIOC,   RW)
#define     RW_Write      	GPIO_ResetBits(GPIOC, RW)

#define     DI          	GPIO_PIN_7      //指令数据选择
#define     DI_Data      	GPIO_SetBits(GPIOC,   DI)
#define     DI_Instruction  GPIO_ResetBits(GPIOC, DI)


void LcdDelay(uint time);
void _NOP_(void);
void LcdWriteCmd(uchar cmd);
void LcdWriteData(uchar data);
void SetOnOff(uchar onoff);
void SelectPage(uchar page);
void SelectColum(uchar colum);
void SelectStartLine(uchar startline);
void SelectScreen(uchar screen);
void ClearScreen(uchar screen);
void InitLcd(void);
void MX_GPIO_Init(void);
void LCDShowEnglishWord(uchar line, uchar colum, uchar *english_word);

#endif
