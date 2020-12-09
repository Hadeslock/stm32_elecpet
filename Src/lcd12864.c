/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: Hades
 * @Date: 2020-12-02 13:08:23
 * @LastEditors: Hades
 * @LastEditTime: 2020-12-09 14:11:05
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
	if(onoff==1){
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
 * @param {*screen：0-选择左屏；1-选择右屏；2-选择两块屏}
 * @return {*}
 */
void SelectScreen(uchar screen)
{
	switch(screen)
	{
		case 0:
			SET_CS1;HAL_Delay(5);		//开启左屏幕
			RESET_CS2;HAL_Delay(5);		//关闭右屏幕
			break;
		case 1:
			RESET_CS1;HAL_Delay(5);		//关闭左屏幕
			SET_CS2;HAL_Delay(5);		//开启右屏幕
			break;
		case 2:
			SET_CS1;HAL_Delay(5);		//开启左屏幕
			SET_CS2;HAL_Delay(5);		//开启右屏幕
			break;
	}
} 


/**********************************
显示一个英文字符
**********************************/
void Show_english(uchar line,uchar column,uchar *address)
{
	uchar i;
	SelectPage(line);
	SelectColum(column);
	for(i=0;i<8;i++)
	{
		LcdWriteData(*address);
		address++;	
	}
	
	SelectPage(line+1);
	SelectColum(column);
	for(i=0;i<8;i++)
	{
		LcdWriteData(*address);
		address++;	
	}
}


/**
 * @description: 清屏函数
 * @param {*}
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
	SetOnOff(0);			//显示关
	ClearScreen(2);			//清屏
	SelectPage(0);			//页设置
	SelectColum(0);			//列设置
	SelectStartLine(0);		//设置起始页
	SetOnOff(1);			//显示开
}

/**
 * @description: GPIO端口配置
 */
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	//Init the data pin
	GPIO_InitStruct.Pin = DATA;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//Init the control pin
	GPIO_InitStruct.Pin = CS1|CS2|E|RW|DI;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
}


/**
 * @description: 在colum这一列(默认第0行)开始显示一块width*height的数据
 * @param {*colum：在这一行开始显示
 * 			width：显示数据的宽度
 * 			height：显示数据的高度
 * 			address：储存显示数据的(uchar)数组地址指针}
 * @return {*}
 */
void ShowInColum(uchar colum, uchar width, uchar height, uchar *address){
	int page = 0;
	for(page = 0; page < height/8; page++){	//依次显示各页的内容
		SelectPage(page);
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
 * @note: 以(x,y)为顶点，显示一张图片(pic_width*pic_height)
 * @param {*x:图片顶点的横坐标(从1到128-pic_width+2)
 * 			y:图片顶点的纵坐标(从1到64-pic_height+2)
 * 			pic_width：图片的像素宽度
 * 			pic_height：图片的像素高度(列行式采样，pic_height必然是8的整数倍)
 * 			picture：储存图片的(uchar)数组地址指针}
 * @return {*}
 */
void LCDShowPicture(uchar x, uchar y, uchar pic_width, uchar pic_height, uchar *picture){
	uchar left_width = 0, right_width = 0;	//左屏和右屏的显示内容宽度
	uchar overlap_width = pic_width - 1;	//交叠的跨屏区域宽度

	if (y >= (64-(pic_height-1)+1)){	//显示区域溢出
		return;
	}
	SelectStartLine(y);		//起始行设到显示的顶点所在行

	//只有左屏有显示
	if(x >= 1 && x <= (64-overlap_width)){
		RESET_CS1;SET_CS2;	//开左屏，关右屏
		ShowInColum(x,pic_width,pic_height,picture);
	}

	//只有右屏有显示
	else if(x >= 65 && x <= (128-overlap_width)){
		SET_CS1;RESET_CS2;	//关左屏，开右屏
		ShowInColum(x,pic_width,pic_height,picture);
	}

	//左右屏都有显示
	else if(x >= (64-overlap_width+1) && x <= 64){
		left_width = 63 - x + 1;
		right_width = pic_width - left_width;
		//左屏显示
		RESET_CS1;SET_CS2;	//开左屏，关右屏
		ShowInColum(x,left_width,pic_height,picture);
		//右屏显示
		SET_CS1;RESET_CS2;	//关左屏，开右屏
		ShowInColum(x,right_width,pic_height,picture);
	}
}

/**
 * @brief: 显示英文字母
 * @note: 以(x,y)为顶点，显示一个英文字母(8*16)
 * @param {*x:英文字母顶点的横坐标(从1到128-pic_width+2)
 * 			y:英文字母顶点的纵坐标(从1到64-pic_height+2)
 * 			english_word：储存英文字母的(uchar)数组地址指针}
 * @return {*}
 */
void LCDShowEnglishWord(uchar x, uchar y, uchar *english_word){
	uchar word_width = 8, word_height = 16;
	LCDShowPicture(x,y,word_width,word_height,english_word);
}
