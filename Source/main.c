
	#include<main.h>

	/*================================Funtion prototype=========================================*/
	void extract_buff();
	void calc_disp();
	void reset_buff();
	void reverse(char* str, int len);
	int intToStr(int x, char str[], int d);
	void ftoa(float n, char* res, int afterpoint);
	double round(double soCanLamTron, int chuSo);
	void xuly();
	void disp_error();
	void disp_over();
	/*========================================END=================================================*/
	
	
	
	/*====================================Variables==============================================*/
	/*Data (252.1B) include: Idata (131Bytes) + Data (remain 16bytes) + etc...
	xdata: rat nhieu
	float, double, long double,long, unsigned long = 4 bytes
	int: 2bytes
	char, usigned char: 1byte
	xdata volatile int pointer =0;

	max float 32767 => Du 16bit nhung phai sd bit lam bit dau, exp, k dc luu tai xdata\
	buff result cung k dc luu tai xdata
	data float kq = 320.967545454; 
	*/
	
	
	idata unsigned char buff[25];		// Buffer save string of eqution
	idata unsigned char tt1[10];
	idata unsigned char tt2[10]; 		// Two string buffers save two oprerants of Equation
	idata volatile int pointer = 0;	//Pointer to devide buff string
	idata unsigned char buff_result[10];	//Ket qua dc luu vao mang ki tu
	idata unsigned char error[]= "Math Error";
	idata int flag_error = 0;
	idata int negative = 0;
	idata int over_mem = 0;
	idata unsigned char over_mes[]="Memory Over";
	
	data float f_operant = 0;
	data float l_operant = 0;			//Two interger for store two oprerants in float
	data unsigned char sign;			// Store sign of equation
	data float result = 0;				// Store the result
	data unsigned char key = 0;		// Where key pressed is located	
	/*==========================================END===============================================*/

void main()
{
	reset_buff();
	LCD_Init();   				//Thiet lap cau hinh cho LCD
	LCD_Clear();
	LCD_Gotoxy(0,0);
	LCD_PutString("Hi there!");
	delay_ms(1000);
	LCD_Clear_Blink();
	while(1)
	{
		key = KEY4X4_GetKey();			//nhan thu tu phim nhan
		if (key!=0){								//phat hien co phim nhan
			if (key !='C'){
				LCD_PutChar(key);	
				delay_ms(250);
				buff[pointer] = key;
				pointer++;
				if (key =='='){
					extract_buff();
					calc_disp();
					reset_buff();				//Tinh xong xoa bo nho dem
				}
			}
			else{ 
				LCD_Clear_Blink();	//Nhan C => Xoa man hinh
				reset_buff();
			}
		}	
	}
}

void extract_buff(){ 
	int k = 0;
	pointer = 0;					// 656565+65545=
	
	while(buff[pointer]!='+'&&buff[pointer]!='-'&&buff[pointer]!='X'&&buff[pointer]!=':'){
		tt1[pointer] = buff[pointer];
		pointer++;
	}
	sign = buff[pointer];
	pointer++;
	k = pointer;
	while(buff[pointer] != '='){
		tt2[pointer - k] = buff[pointer];
		pointer++;
	}
}

void calc_disp(){
	int i = 0;
	idata unsigned char verify[10];
	f_operant = atoi(tt1);
	l_operant = atoi(tt2);
	
	switch (sign){
		case '+':
			result = f_operant + l_operant;
			break;
		case '-':
			result = f_operant - l_operant;
			break;
		case 'X':
			result = f_operant * l_operant;
			break;
		case ':':
			if (l_operant !=0){
			result = f_operant / l_operant;
			}
			else flag_error = 1;
			break;
		default:
			flag_error = 1;
	}
	ftoa(result,verify,3);
	for (i=0;i<=strlen(verify);i++){
		if (verify[i] == '/'||verify[i] == '+'||verify[i] == '-')
			over_mem = 1;
	}

	if (sign == '/'){
		result = round(result,3);
		xuly();
	}
	else
		xuly();
	memset(verify,0,strlen(verify));
}
void xuly(){
		if (result < 0 && flag_error == 0 && over_mem == 0){
			result = -result;
			ftoa(result,buff_result,3);
			//LCD_Clear();
			LCD_control_off_xy(0,1);
			LCD_PutChar('-');
			LCD_PutString(buff_result);
		}
		else if(result >=0 && flag_error == 0 && over_mem == 0){
			ftoa(result,buff_result,3);
			//LCD_Clear();
			LCD_control_off_xy(0,1);
			LCD_PutString(buff_result);
		}
		else {
			if (over_mem == 1 && flag_error == 0)
				disp_over();
			else
				disp_error();
		}
}
void disp_error(){
	LCD_Clear();
	LCD_control_off_xy(0,0);
	LCD_PutString(error);
}
void disp_over(){
	LCD_Clear();
	LCD_control_off_xy(0,0);
	LCD_PutString(over_mes);
}
double round(double soCanLamTron, int chuSo)
{
    int temp;
    int i, result = 1;
   
    //Pow
    for(i = 1; i <= chuSo; i++)
    {
        result *= 10;
    }
    temp = soCanLamTron*result;
    if(temp%10 >= 5)
    {
        temp += 1;
    }
    soCanLamTron = (double)temp/result;
    return soCanLamTron;
}
void reset_buff(){
	memset(buff,0,strlen(buff));
	memset(tt1,0,strlen(tt1));
	memset(tt2,0,strlen(tt2));
	memset(buff_result,0,strlen(buff_result));
	sign = 'n';
	pointer = 0;
	flag_error = 0;
	over_mem = 0;
}
	
// Reverses a string 'str' of length 'length'
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
int intToStr(int x, char str[], int d){
	int i = 0;
	while (x) {
	str[i++] = (x % 10) + '0';
	x = x / 10;
}

// If number of digits required is more, then
// add 0s at the beginning
while (i < d) str[i++] = '0';
reverse(str, i);
str[i] = '\0';
return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint){
// Extract integer part
int ipart = (int)n;
// Extract floating part
float fpart = n - (float)ipart;
// convert integer part to string
int i = intToStr(ipart, res, 0);
// check for display option after point
if (afterpoint != 0){
	res[i] = '.'; // add dot
	// Get the value of fraction part upto given no.
	// of points after dot. The third parameter
	// is needed to handle cases like 233.007
	fpart = fpart * pow(10, afterpoint);
	intToStr((int)fpart, res + i + 1, afterpoint);
}
}