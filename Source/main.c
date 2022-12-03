//===========================khai bao cac thu vien can su dung==============//
#include<main.h>





//===========================dinh nghia cac chan vao ra======================//
//============================khai bao bien va hang==========================//
unsigned char key=0;
unsigned char buff[20];						// Bo nho dem buff, Luu bien vung
char buff_result[20];
float result = 0;

	
//============================HAM MAIN=======================================//
int main()
	{


			LCD_Init();   //Thiet lap cau hinh cho LCD
			Keypad_Init();		//goi ham khai bao cac chan ma tran phim 4x4

			while(1)
				{
						// Get key pressed
						key = KEY4X4_GetKey();//nhan thu tu phím nhan
						if (key!=0)//phat hien co phim nhan
							{
								LCD_Gotoxy(0,0);	//hien thi tai toa do x,y=(0,0)
								LCD_PutChar(key);	//hien thi ky tu phim ta LCD
							}
				}
	}