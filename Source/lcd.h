#ifndef _LCD_H
#define _LCD_H
#include<main.h>
//=========================khai bao cac chan vao ra============================//
//	DINH NGHIA CAC CHAN/PORT
sbit LCD_RS=P2^0;//khai bao chan RS cua LCD o P2.0
sbit LCD_RW=P2^2;//khai bao chan RW cua LCD o P2.1
sbit LCD_EN=P2^1;//khai bao chan EN cua LCD o P2.2

sbit LCD_D4=P0^4;//khai bao chan D4 cua LCD o P0.4
sbit LCD_D5=P0^5;//khai bao chan D4 cua LCD o P0.5
sbit LCD_D6=P0^6;//khai bao chan D4 cua LCD o P0.6
sbit LCD_D7=P0^7;//khai bao chan D4 cua LCD o P0.7

/*
	KHAI BÁO CÁC HÀM CHO LCD
*/
void LCD_Init ( void );      								//ham khoi tao LCD16x2
void LCD_Enable(void);       								//ham tao xung EN
void LCD_Clear(void);            						//xoa noi dung hien thi tren LCD16x2
void LCD_Send4Bit(unsigned char _data );						//ham goi du lieu 4 bit den LCD16x2
void LCD_SendCommand (unsigned char  command,unsigned char reg );//Goi 1 byte du lieu den LCD
void LCD_Gotoxy(unsigned char  x, unsigned char y);			//ham thiet lap vi tri con tro
void LCD_PutChar ( unsigned char  _data );					//ham viet mot ky tu len LCD16x2
void LCD_PutString (unsigned char *s); 						// hien thi chuoi ky tu ra LCD     
void LCD_Number(unsigned long number,unsigned char leng);//ham viet mot chuoi so len LCD16x2
void LCD_control_blink_xy(unsigned char x, unsigned char y);	//hàm hien thi con tro nhap nhay
void LCD_control_off_xy(unsigned char x, unsigned char y);	//hàm tat con tro nhap nhay
#endif