/*
 * @Description: lcd12864的显示函数头文件
 * @Author: Hades
 * @Date: 2020-12-02 13:10:45
 * @LastEditors: Hades
 * @LastEditTime: 2020-12-10 17:43:46
 */

#ifndef _LCD12864_H
#define _LCD12864_H

#define uchar unsigned char
#define uint unsigned int

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


/**
 * @description: 控制显示开关函数
 * @param {*onoff:1-显示开；0-显示关}
 * @return {*}
 */
void SetOnOff(uchar onoff);
/**
 * @description: 显示起始行设置函数
 * @param {*startline：选择的起始行}
 * @return {*}
 */
void SelectStartLine(uchar startline);
/**
 * @description: 选择左右屏函数
 * @param {*screen：LEFT-选择左屏；RIGHT-选择右屏；BOTH-选择两块屏}
 * @return {*}
 */
void SelectScreen(uchar screen);
/**
 * @description: 清屏函数
 * @param {*screen：LEFT-左屏清屏；RIGHT-右屏清屏；BOTH-两块屏清屏}
 * @return {*}
 */
void ClearScreen(uchar screen);
/**
 * @brief: 显示图片函数
 * @note: 在line这一行、colum这一列显示一张图片(pic_width*pic_height)，共8行，128列
 * @param {*line:图片顶点所在行，范围：[0,8-(pic_height/8)]
 * 			colum:图片顶点所在列，范围：[0,128-pic_width]
 * 			pic_width：图片的像素宽度
 * 			pic_height：图片的像素高度(列行式采样，pic_height必然是8的整数倍)
 * 			picture：储存图片的(uchar)数组地址指针}
 * @return {*}
 */
void LCDShowPicture(uchar line, uchar colum, uchar pic_width, uchar pic_height, uchar *picture);
/**
 * @brief: 显示英文字母
 * @note: 在line这一行、colum这一列显示一个英文字母(8*16)
 * @param {*line:英文字母顶点像素所在行，范围：[0,6]
 * 			colum:英文字母顶点像素所在列，范围：[0,120]
 * 			english_word：储存英文字母的(uchar)数组地址指针}
 * @return {*}
 */
void LCDShowEnglishWord(uchar line, uchar colum, uchar *english_word);
/**
 * @brief: 显示中文字
 * @note: 在line这一行、colum这一列显示一个中文字(16*16)
 * @param {*line:中文字顶点像素所在行，范围：[0,6]
 * 			colum:中文字顶点像素所在列，范围：[0,112]
 * 			zh_word：储存中文字的(uchar)数组地址指针}
 * @return {*}
 */
LCDShowZhWord(uchar line, uchar colum, uchar *zh_word);

#endif
