//===========================khai bao cac thu vien can su dung==============//
#include<main.h>

void reset_var();
void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char* res, int afterpoint);


unsigned char key=0;
idata char buff_input[20];					// Bo nho dem buff, Luu bien vung max 26
idata char buff_result[10];
//volatile int pointer =0;

void main()
{
			LCD_Init();   			//Thiet lap cau hinh cho LCD
			delay_ms(10);
			//Keypad_Init();			//goi ham khai bao cac chan ma tran phim 4x4
			LCD_Clear();
			delay_ms(10);
			LCD_Gotoxy(0,0);
			delay_ms(10);
			LCD_PutString("Hi there!");
			delay_ms(500);
			reset_var();
			delay_ms(10);
	
			while(1)
				{
						key = KEY4X4_GetKey();		//nhan thu tu ph�m nhan
						if (key!=0)								//phat hien co phim nhan
							{
								if (key !='C')
									{
										LCD_PutChar(key);	//hien thi ky tu phim ta LCD
										
										delay_ms(200);
									}
								else 
										reset_var();
							}	
				}
}
void reset_var()
{
	LCD_Clear();
	LCD_control_blink_xy(0,0);
	
}
// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;

	// Extract floating part
	float fpart = n - (float)ipart;

	// convert integer part to string
	int i = intToStr(ipart, res, 0);

	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}