#ifndef _KEYPAD4X4_H
#define _KEYPAD4X4_H
#include<main.h>
//----------KHAI BAO CAC HAM CHO KEYPAD4X4.C
//=========================khai bao cac chan vao ra============================//
//dinh nghia các chan cot
sbit COL1=P1^0;
sbit COL2=P1^1;
sbit COL3=P1^2;
sbit COL4=P1^3;
//dinh nghia các chan hang
sbit ROW1=P1^4;
sbit ROW2=P1^5;
sbit ROW3=P1^6;
sbit ROW4=P1^7;
/*
	KHAI BÁO CÁC HÀM CHO MA TRAN PHIM 4X4
*/
unsigned char KEY4X4_Push(void);
void KEY4X4_CheckCol(unsigned char Col);
unsigned char KEY4X4_GetKey(void);
void KEY4X4_Init(void);


#endif