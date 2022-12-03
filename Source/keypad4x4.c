#include "keypad4x4.h"
//DINH NGHIA CAC PHIM NHAN
/*
DINH NGHIA MA TRAN [ROW][COL]
*/
unsigned char  KEY_4X4[4][4]=
								{':','9','8','7',	//// TAI (ROW 1, COL1) LA SO 3,(ROW 1, COL2) LA SO 2,(ROW 1, COL3) LA SO 1,(ROW 1, COL4) LA SO 0
								 'X','6','5','4',	//// TAI (ROW 2, COL1) LA SO 7,(ROW 2, COL2) LA SO 6,(ROW 2, COL3) LA SO 5,(ROW 2, COL4) LA SO 4
								 '-','3','2','1',
								 '+','=','0','C'};
/*******************************************************************************
Noi Dung    : Kiem tra xem co phim tren ma tran phim 4x4 duoc nhan khong.
Tham Bien   : Khong.
Tra Ve      : 1 : Co phim tren MTP4x4 duoc bam.
              0 : Khong co phim tren MTP4x4 duoc bam.
********************************************************************************/
								 
unsigned char  KEY4X4_Push(void)
{

	if((ROW1==0)|(ROW2==0)|(ROW3==0)|(ROW4==0))
		return 1;
	else 
		return 0;
}
/*******************************************************************************
Noi Dung    : Quet tung cot tren MTP4x4.
Tham Bien   : COL : cot can quet.
Tra Ve      : Khong.
********************************************************************************/

void KEY4X4_CheckCol(unsigned char Col)
{
	  COL1=1;
		COL2=1;
		COL3=1;
		COL4=1;
	if(Col==1)
	{
		COL1=0;
	}
	else if(Col==2)
	{
		COL2=0;
	}
	else if(Col==3)
	{
		COL3=0;
	}
	else if(Col==4)
	{
		COL4=0;
	}
}

/*******************************************************************************
Noi Dung    : Doc va tra ve gia tri phim duoc bam tren MTP4x4.
Tham Bien   : Khong.
Tra Ve      : Gia tri phim duoc bam.
********************************************************************************/

unsigned char KEY4X4_GetKey(void)
{
	unsigned char i;
	//cho COL1 den COL4 =0
	  COL1=0;
		COL2=0;
		COL3=0;
		COL4=0;
	if(KEY4X4_Push()==1)//phat hien co phim nhan
	{
		delay_ms(1);//chong nhieu
		if(KEY4X4_Push()==1)//xac dinh chac chan co nhan
		{			
			for(i=1;i<5;i++)//quet COL1 den COL3
			{				
				KEY4X4_CheckCol(i);
				
				if(ROW1==0)//neu hang thu 1 co nhan (ROW1)
					{
						return KEY_4X4[0][i-1];	//tra ve ky tu nhan o ROW1 va COL quet tu COL1 den COL4
					}
				else if(ROW2==0)//neu hang thu 2 co nhan (ROW2)
					{
						return KEY_4X4[1][i-1];//tra ve ky tu nhan o ROW2 va COL quet tu COL1 den COL4
					}
				else if(ROW3==0)//neu hang thu 2 co nhan (ROW2)
					{	
						return KEY_4X4[2][i-1];//tra ve ky tu nhan o ROW3 va COL quet tu COL1 den COL4
					}
						
				else if(ROW4==0)//neu hang thu 2 co nhan (ROW2)
					{
						return KEY_4X4[3][i-1];//tra ve ky tu nhan o ROW4 va COL quet tu COL1 den COL4
					}
			}			
		}
	}
	return 0;//khong co nhan
}
/*******************************************************************************
Noi Dung      :   Khai bao cac chan cua phim nhan 4x4
Tham Bien     :   Khong.
Tra Ve        :   Khong.
*******************************************************************************/
void Keypad_Init()
	{
		//ban dau cho COL =0
		COL1=0;
		COL2=0;
		COL3=0;
		COL4=0;
		//ban dau cho ROW =1
		ROW1=1;
		ROW2=1;
		ROW3=1;
		ROW4=1;
	}