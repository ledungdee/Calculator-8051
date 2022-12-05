#include "lcd.h"
/* =============LCD 16x2====================== */
/*******************************************************************************
Noi Dung      :   Gui tin hieu Enable den LCD16X2.
Tham Bien     :   Khong.
Tra Ve        :   Khong.
*******************************************************************************/
 void LCD_Enable(void)
{
    LCD_EN=1;//cho chan EN len muc cao
    delay_us(30);
		LCD_EN=0;//cho chân EN xuong muc thap
    delay_us(50);
}

/*******************************************************************************
Noi Dung      :   Ham goi 1 byte ra LCD16X2.
Tham Bien     :   data: du liwu can goi, reg: chon thanh ghi du lieu hay thanh ghi lenh
Tra Ve        :   Khong.
*******************************************************************************/
 void LCD_Send4Bit (unsigned char _data )
{
		LCD_D4 = _data& 0x01; //=>0x01=0b00000001=> goi bit dau tien
		LCD_D5 = (_data>>1)&1;//=>dich sang phai 1 bit roi xuat ra bit thu 2
		LCD_D6 = (_data>>2)&1;//=>dich sang phai 1 bit roi xuat ra bit thu 3
		LCD_D7 = (_data>>3)&1;//=>dich sang phai 1 bit roi xuat ra bit thu 4
}
 /*******************************************************************************
Noi Dung    :   Gui 1 byte du lieu den LCD.
Tham Bien   :   command: byte du lieu can goi; reg chon thanh ghi lenh hay du lieu
Tra Ve      :   Khong.
********************************************************************************/

void LCD_SendCommand (unsigned char  command,unsigned char reg )
{
	 if(reg==0)//reg=0 hay chan RS=0 thi chon thanh ghi lenh
   {
		LCD_RS=0;	// chon thanh ghi lenh
   }
  else//reg=1 hay RS=1 chon thanh ghi du lieu
   {
    LCD_RS=1;		// chon thanh ghi du lieu
   }
		LCD_Send4Bit  ( command >>4 );   /* Gui 4 bit cao */
		LCD_Enable () ;
		LCD_Send4Bit  ( command  );      /* Gui 4 bit thap*/
		LCD_Enable () ;
}
/*******************************************************************************
Noi Dung     :   Xoa noi dung hien thi tren LCD16X2.
Tham Bien    :   Khong.
Tra Ve       :   Khong.
********************************************************************************/
void LCD_Clear()
{
    LCD_SendCommand(0x01,0);// goi lenh dieu khien LCD
    delay_ms(5);
}
/*******************************************************************************
Noi Dung     :   Khoi tao LCD16X2.
Tham Bien    :   Khong.
Tra Ve       :   Khong.
*******************************************************************************/
 void LCD_Init ( void )
{
    LCD_RS=0;
	  LCD_RW=0;
    LCD_EN=0;
    LCD_Send4Bit(0x03);// goi du lieu cho LCD16x2 kieu mat dinh, dua con tro ve dau dong dau tien
    LCD_Enable();
    delay_us(10);
    LCD_Send4Bit(0x02);// goi du lieu cho LCD16x2 kieu mat dinh, dua con tro ve dau dong dau tien
    LCD_Enable();
    delay_us(10);
    LCD_SendCommand(0x28,0);// ghi lenh: giao thuc 4 bit, hien thi 2 hang, ki tu 5x7
    LCD_SendCommand(0x0C,0);// ghi lenh: cho phep hien thi man hinh
    LCD_Clear();           // xoa toan bo khung hinh
}
/*******************************************************************************
Noi Dung     :   Thiet lap vi tri con tro LCD16X2.
Tham Bien    :   x: vi tri cot cua con tro. x = 0 -> 15.
                 y: vi tri hang cua con tro. y= 0,1.
Tra Ve       :   Khong.
********************************************************************************/
void LCD_Gotoxy(unsigned char x, unsigned char y)
{
  unsigned char  address;
  if(!y)
        address = (0x80+x);
  else
        address = (0xC0+x);

  delay_ms(5);
  LCD_SendCommand(address,0);	//ghi lenh dieu khien LCD
}
/*******************************************************************************
Noi Dung    :   Viet 1 ki tu len LCD16X2.
Tham Bien   :   Data  :   Gia tri ki tu can hien thi.
Tra Ve      :   Khong.
********************************************************************************/
 void LCD_PutChar (unsigned char _data )
{
    LCD_SendCommand(_data,1);// ghi du lieu
		delay_us(5);

}
/*******************************************************************************
Noi Dung    :   Viet 1 chuoi ki tu len LCD16X2.
Tham Bien   :   *s   :  chuoi du lieu can hien thi.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_PutString (unsigned char *s)
{

    while (*s)
    {
        LCD_PutChar(*s);
        s++;
    }
}
/*******************************************************************************
Noi Dung    :   Hin thi so len LCD16X2.
Tham Bien   :   number  : so can hien thi, leng la chieu dai cua chuoi so
Tra Ve      :   Khong.
********************************************************************************/
void LCD_Number(unsigned long number,unsigned char leng)
{
//leng la chieu dai cua chuoi so
unsigned char i;
char CacKyTu[20];//mang chua cac ky tu so
unsigned char temp;

	for(i=0; i<leng; i++)
	{
		temp = number % 10;
		number = number/10;
		CacKyTu[i] = temp;
	}
	for(i=0; i<leng; i++)
	{
		LCD_SendCommand(CacKyTu[leng-1-i] + 48,1);
	}
}
/*******************************************************************************
Noi Dung    :   hàm hien thi con tro nhap nhay
Tham Bien    :   x: vi tri cot cua con tro. x = 0 -> 15.
                 y: vi tri hang cua con tro. y= 0,1.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_control_blink_xy(unsigned char x, unsigned char y)
{
		LCD_Gotoxy(x,y);
		LCD_SendCommand(0x0f,0);
}
/*******************************************************************************
Noi Dung    :   hàm tat con tro nhap nhay
Tham Bien    :   x: vi tri cot cua con tro. x = 0 -> 15.
                 y: vi tri hang cua con tro. y= 0,1.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_control_off_xy(unsigned char x, unsigned char y)
{
	LCD_Gotoxy(x,y);
	LCD_SendCommand(0x0E,0);
}

/*******************************************************************************
Noi Dung    :   hàm tat con tro nhap nhay
Tham Bien    :   x: vi tri cot cua con tro. x = 0 -> 15.
                 y: vi tri hang cua con tro. y= 0,1.
Tra Ve      :   Khong.
********************************************************************************/
void LCD_Clear_Blink()
	{
		LCD_Clear();
		LCD_control_blink_xy(0,0);
	}