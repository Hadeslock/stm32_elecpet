/*
 * @Descripttion: lcd12864的显示函数库
 * @Author: Hades
 * @Date: 2020-12-02 13:08:23
 * @LastEditors: Hades
 * @LastEditTime: 2020-12-10 17:43:30
 */

#include "lcd12864.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"


/**
 * @description: 延时函数
 * @param {*}
 * @return {*}
 */
void LcdDelay(uint time)
{
	while(time--);
}

/**
 * @description: 空指令函数，起延时效果
 * @param {*}
 * @return {*}
 */
void _NOP_(void)
{
    uint i = 200;
    while(i > 0)
		{
        i--;
    }
}

/**
 * @description: 指令写入函数，指令通过8个数据端口输入LCD
 * @param {*cmd:输入的8位指令}
 * @return {*}
 */
void LcdWriteCmd(uchar cmd)
{
	DI_Instruction;			//指令模式
	RW_Write;			//设置写入
	E_H;			//接受指令输入	
	DATABUS->ODR = (DATABUS->ODR & 0xff00)|cmd;  //DATABUS=cmd;
	_NOP_();
	E_L; 		//e=0;
	_NOP_();
}

/**
 * @description: 数据写入函数
 * @param {*data:写入的数据}
 * @return {*}
 */
void LcdWriteData(uchar data)
{
	E_H;		//e=1;
	RW_Write;		//RW=0;
	DI_Data;		//RS=1;
	DATABUS->ODR =	(DATABUS->ODR & 0xff00)|data;	//DATABUS=data;
  _NOP_();
	E_L;		//e=0;
  _NOP_();
}

/**
 * @description: 控制显示开关函数
 * @param {*onoff:1-显示开；0-显示关}
 * @return {*}
 */
void SetOnOff(uchar onoff)
{
	if(onoff==ON){
		LcdWriteCmd(0x3f);	
	}	
	else{
		LcdWriteCmd(0x3e);
	}
}


/**
 * @description: 页选择函数，12864总共有8页（0~7），每页有8行
 * @param {*page：选择的页}
 * @return {*}
 */
void SelectPage(uchar page)
{
	page = page & 0x07;	  		//只取后三位xxxx x111  ，这3个是要改变位置的数据
	page = page | 0xb8;	  		//页设置的固定格式
	LcdWriteCmd(page);
}


/**
 * @description: 列选择函数，12864每半屏有64列（0~63），分为左右2屏
 * @param {*column：选择的列}
 * @return {*}
 */
void SelectColum(uchar colum)
{
	colum = colum & 0x3f;	 //xx11 1111,这个是要改变Y位置的数据
	colum = colum | 0x40;	 //固定格式
	LcdWriteCmd(colum);
}


/**
 * @description: 显示起始行设置函数
 * @param {*startline：选择的起始行}
 * @return {*}
 */
void SelectStartLine(uchar startline)
{
	startline = startline % 64;			//将输入参数规范到0~63，提高可用性
	startline = startline & 0x3f;		//xx11 1111,这个是要改变x位置的数据
	startline = startline | 0xc0;		//11xxxxxx，是起始行设置的固定指令
	LcdWriteCmd(startline);
}


/**
 * @description: 选择左右屏函数
 * @param {*screen：LEFT-选择左屏；RIGHT-选择右屏；BOTH-选择两块屏}
 * @return {*}
 */
void SelectScreen(uchar screen)
{
	switch(screen)
	{
		case LEFT:
			SET_CS1;HAL_Delay(5);		//开启左屏幕
			RESET_CS2;HAL_Delay(5);		//关闭右屏幕
			break;
		case RIGHT:
			RESET_CS1;HAL_Delay(5);		//关闭左屏幕
			SET_CS2;HAL_Delay(5);		//开启右屏幕
			break;
		case BOTH:
			SET_CS1;HAL_Delay(5);		//开启左屏幕
			SET_CS2;HAL_Delay(5);		//开启右屏幕
			break;
	}
} 


/**
 * @description: 清屏函数
 * @param {*screen：LEFT-左屏清屏；RIGHT-右屏清屏；BOTH-两块屏清屏}
 * @return {*}
 */
void ClearScreen(uchar screen)
{
	uchar i,j;
	SelectScreen(screen);
	for(i=0;i<8;i++)
	{
		SelectPage(i);
		SelectColum(0);
		for(j=0;j<64;j++)
		{
			LcdWriteData(0);			
		}	
	}
}

/**
 * @description: lcd12864初始化函数
 * @param {*}
 * @return {*}
 */
void InitLcd()
{
	SetOnOff(OFF);			//显示关
	ClearScreen(BOTH);		//清屏
	SelectPage(0);			//页设置
	SelectColum(0);			//列设置
	SelectStartLine(0);		//设置起始行
	SetOnOff(ON);			//显示开
}


/**
 * @brief: 显示核心函数
 * @note: 在line这一行、colum这一列显示一张图片(pic_width*pic_height)
 * @param {*line：顶点像素所在行
 * 			colum：顶点像素所在列
 * 			width：显示数据的宽度
 * 			height：显示数据的高度
 * 			address：储存显示数据的(uchar)数组地址指针}
 * @return {*}
 */
void ShowInColum(uchar line, uchar colum, uchar width, uchar height, uchar *address){
	int page = 0;
	for(page = 0; page < height/8; page++){	//依次显示各页的内容
		SelectPage(line + page);
		SelectColum(colum);
		for (int i = 0; i < width; i++)
		{
			LcdWriteData(*address);
			address++;
		}
	}
}


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
void LCDShowPicture(uchar line, uchar colum, uchar pic_width, uchar pic_height, uchar *picture){
	uchar left_width = 0, right_width = 0;	//左屏和右屏的显示内容宽度
	uchar overlap_width = pic_width - 1;	//交叠的跨屏区域宽度

	if (line>(8-(pic_height/8)) || colum>128-pic_width){	//显示区域溢出
		return;
	}
	//只有左屏有显示
	if(colum <= (63-overlap_width)){
		SelectScreen(LEFT);
		ShowInColum(line,colum,pic_width,pic_height,picture);
	}
	//只有右屏有显示
	else if(colum >= 64 && colum <= (127-overlap_width)){
		SelectScreen(RIGHT);
		ShowInColum(line,colum,pic_width,pic_height,picture);
	}
	//左右屏都有显示
	else if(colum >= (63-overlap_width+1) && colum <= 63){
		left_width = 63 - colum + 1;
		right_width = pic_width - left_width;
		//左屏显示
		SelectScreen(LEFT);
		ShowInColum(line,colum,left_width,pic_height,picture);
		//右屏显示
		SelectScreen(RIGHT);
		ShowInColum(line,colum,right_width,pic_height,picture);
	}
}

/**
 * @brief: 显示英文字母
 * @note: 在line这一行、colum这一列显示一个英文字母(8*16)
 * @param {*line:英文字母顶点像素所在行，范围：[0,6]
 * 			colum:英文字母顶点像素所在列，范围：[0,120]
 * 			english_word：储存英文字母的(uchar)数组地址指针}
 * @return {*}
 */
void LCDShowEnglishWord(uchar line, uchar colum, uchar *english_word){
	uchar word_width = 8, word_height = 16;
	if(line>6 || colum>120){	//判断地址是否合法
		return;
	}
	LCDShowPicture(line,colum,word_width,word_height,english_word);
}


/**
 * @brief: 显示中文字
 * @note: 在line这一行、colum这一列显示一个中文字(16*16)
 * @param {*line:中文字顶点像素所在行，范围：[0,6]
 * 			colum:中文字顶点像素所在列，范围：[0,112]
 * 			zh_word：储存中文字的(uchar)数组地址指针}
 * @return {*}
 */
LCDShowZhWord(uchar line, uchar colum, uchar *zh_word){
	uchar word_width = 16, word_height = 16;
	if(line>6 || colum>112){	//判断地址是否合法
		return;
	}
	LCDShowPicture(line,colum,word_width,word_height,zh_word);
}
