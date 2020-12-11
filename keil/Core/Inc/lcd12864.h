/*
 * @Description: lcd12864的显示函数头文件
 * @Author: Hades
 * @Date: 2020-12-10 20:53:37
 * @LastEditors: Hades
 * @LastEditTime: 2020-12-10 21:09:37
 */

#ifndef _LCD12864_H
#define _LCD12864_H

#include "main.h"


#define ON 1
#define OFF 0

#define LEFT 0
#define RIGHT 1
#define BOTH 2

#define     DATABUS     		GPIOB
#define     DATA        		DB0_Pin|DB1_Pin|DB2_Pin|DB3_Pin|DB4_Pin|DB5_Pin|DB6_Pin|DB7_Pin

#define     SET_CS1       	HAL_GPIO_WritePin(CS1_N_GPIO_Port, CS1_N_Pin, GPIO_PIN_RESET)//左屏幕选择，低电平有效
#define     RESET_CS1       HAL_GPIO_WritePin(CS1_N_GPIO_Port, CS1_N_Pin, GPIO_PIN_SET)
    
#define     SET_CS2       	HAL_GPIO_WritePin(CS2_N_GPIO_Port, CS2_N_Pin, GPIO_PIN_RESET)//右屏幕选择，低电平有效
#define     RESET_CS2       HAL_GPIO_WritePin(CS2_N_GPIO_Port, CS2_N_Pin, GPIO_PIN_SET)

#define     LCD_ENABLE			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET)//指令数据控制
#define     LCD_DISABLE			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET)
     
#define     RW_Read					HAL_GPIO_WritePin(R_W_GPIO_Port, R_W_Pin, GPIO_PIN_SET)//读写控制
#define     RW_Write      	HAL_GPIO_WritePin(R_W_GPIO_Port, R_W_Pin, GPIO_PIN_RESET)

#define     DI_Data					HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET)//指令数据选择
#define     DI_Instruction  HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET)


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
void LCDShowZhWord(uchar line, uchar colum, uchar *zh_word);


#endif

