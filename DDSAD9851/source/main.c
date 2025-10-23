#include "STC12C5A60S2.H"
#include "stdio.h"
#include "DDS9851.H"
#include "bsp_seg.h"
#define KEY_MATRIX_PORT	P1	//使用宏定义矩阵按键控制口

unsigned char seg_string[10]; 
unsigned char seg_buf[8];
unsigned char pos = 0;	
unsigned char Key_Value = 0;
unsigned char Key_Down = 0;
unsigned char Key_Old = 0;
unsigned char Key_Up = 0;
unsigned char state_flag = 0;

void Seg_Proc(void);
void Key_Proc(void);


u8 key_matrix_ranks_scan(void);

double Fre = 40000000;

void init(void)
{
	P0=0x00;
	P1=0x00;
	P2=0x00;
	P3=0xff;
}
void main()
{
	init();
	ad9851_wr_serial(0x01, Fre);	//0X00为不开六备频 0X01为开六备频
	while(1)
	{
		ad9851_wr_serial(0x01, Fre);
		//ad9851_wr_phase_serial(90);
		Seg_Proc();
		Key_Proc();
	}
}



void Seg_Proc()
{
	switch(state_flag)
	{
		case 0x00:
			sprintf(seg_string,"F-----%2d",(unsigned int)(Fre/1000000));
		break;
		case 0x02:
			sprintf(seg_string , "----    ");
			break;
		default:
			sprintf(seg_string,"1243    ");
			break;
	}
	Seg_Tran(seg_string,seg_buf);
	Seg_Disp(seg_buf);
}

void Key_Proc()
{
	Key_Value = key_matrix_ranks_scan();
	Key_Down = Key_Value&(Key_Value^Key_Old);
	Key_Up = ~(Key_Value&(Key_Value^Key_Old));
	Key_Old = Key_Value;
	switch(Key_Down)
	{
		case 1:
			Fre += 1000000;
			break;
		case 2:
			Fre -= 1000000;
			break;
		case 3:
			state_flag += 0x01;
			break;
		default:
			break;
		
	}
}
u8 key_matrix_ranks_scan(void)
{
	u8 key_value=0;

	KEY_MATRIX_PORT=0xf7;//给第一列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xf7)//判断第一列按键是否按下
	{
		delay_10us(1000);//消抖
		switch(KEY_MATRIX_PORT)//保存第一列按键按下后的键值	
		{
			case 0x77: key_value=1;break;
			case 0xb7: key_value=5;break;
			case 0xd7: key_value=9;break;
			case 0xe7: key_value=13;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xf7);//等待按键松开	
	
	KEY_MATRIX_PORT=0xfb;//给第二列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfb)//判断第二列按键是否按下
	{
		delay_10us(1000);//消抖
		switch(KEY_MATRIX_PORT)//保存第二列按键按下后的键值	
		{
			case 0x7b: key_value=2;break;
			case 0xbb: key_value=6;break;
			case 0xdb: key_value=10;break;
			case 0xeb: key_value=14;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfb);//等待按键松开	
	
	KEY_MATRIX_PORT=0xfd;//给第三列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfd)//判断第三列按键是否按下
	{
		delay_10us(1000);//消抖
		switch(KEY_MATRIX_PORT)//保存第三列按键按下后的键值	
		{
			case 0x7d: key_value=3;break;
			case 0xbd: key_value=7;break;
			case 0xdd: key_value=11;break;
			case 0xed: key_value=15;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfd);//等待按键松开	
	
	KEY_MATRIX_PORT=0xfe;//给第四列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfe)//判断第四列按键是否按下
	{
		delay_10us(1000);//消抖
		switch(KEY_MATRIX_PORT)//保存第四列按键按下后的键值	
		{
			case 0x7e: key_value=4;break;
			case 0xbe: key_value=8;break;
			case 0xde: key_value=12;break;
			case 0xee: key_value=16;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfe);//等待按键松开
	
	return key_value;		
}