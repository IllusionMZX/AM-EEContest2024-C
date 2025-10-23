#include "bsp_seg.h"

void delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}


void Seg_Tran(unsigned char *seg_string, unsigned char *seg_buf)
{
	
	unsigned char i = 0;//buf[i],i=0~7
	unsigned char j = 0;//seg_string[j],j = 0~10
	unsigned char temp;//字符串转换为段码的中间存储变量
	
	for(i=0;i<=7;i++,j++)
	{
		switch(seg_string[j])
		{
			case '0':temp = 0x3f;break;
			case '1':temp = 0x06;break;
			case '2':temp = 0x5b;break;
			case '3':temp = 0x4f;break;
			case '4':temp = 0x66;break;
			case '5':temp = 0x6d;break;
			case '6':temp = 0x7d;break;
			case '7':temp = 0x07;break;
			case '8':temp = 0x7f;break;
			case '9':temp = 0x6f;break;
			
			case 'A':temp = 0x77;break;
			case 'B':temp = 0x7c;break;
			case 'C':temp = 0x39;break;
			case 'D':temp = 0x5e;break;
			case 'E':temp = 0x79;break;
			case 'F':temp = 0x71;break;
			

			case '-':temp = 0x40;break;
			case ' ':temp = 0x00;break;
			
			default:temp = 0xff;break;
		}
		if(seg_string[j+1] == '.')
		{
			temp &= 0x80;
			j++;//跳过带“.”的位置
		}
		seg_buf[i] = temp;
		
	}
	
}

void Seg_Disp(unsigned char *seg_buf)
{
	unsigned char i = 0;
	for(i=0;i<8;i++)
	{
	switch(i)//位选
		{
			case 0: LSC=1;LSB=1;LSA=1;break;
			case 1: LSC=1;LSB=1;LSA=0;break;
			case 2: LSC=1;LSB=0;LSA=1;break;
			case 3: LSC=1;LSB=0;LSA=0;break;
			case 4: LSC=0;LSB=1;LSA=1;break;
			case 5: LSC=0;LSB=1;LSA=0;break;
			case 6: LSC=0;LSB=0;LSA=1;break;
			case 7: LSC=0;LSB=0;LSA=0;break;
		}
		P0 = seg_buf[i];
		delay_10us(100);
		P0 = 0x00;
	}
}

