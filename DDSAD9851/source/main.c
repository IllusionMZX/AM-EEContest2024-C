#include "STC12C5A60S2.H"
#include "stdio.h"
#include "DDS9851.H"
#include "bsp_seg.h"
#define KEY_MATRIX_PORT	P1	//ʹ�ú궨����󰴼����ƿ�

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
	ad9851_wr_serial(0x01, Fre);	//0X00Ϊ��������Ƶ 0X01Ϊ������Ƶ
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

	KEY_MATRIX_PORT=0xf7;//����һ�и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xf7)//�жϵ�һ�а����Ƿ���
	{
		delay_10us(1000);//����
		switch(KEY_MATRIX_PORT)//�����һ�а������º�ļ�ֵ	
		{
			case 0x77: key_value=1;break;
			case 0xb7: key_value=5;break;
			case 0xd7: key_value=9;break;
			case 0xe7: key_value=13;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xf7);//�ȴ������ɿ�	
	
	KEY_MATRIX_PORT=0xfb;//���ڶ��и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfb)//�жϵڶ��а����Ƿ���
	{
		delay_10us(1000);//����
		switch(KEY_MATRIX_PORT)//����ڶ��а������º�ļ�ֵ	
		{
			case 0x7b: key_value=2;break;
			case 0xbb: key_value=6;break;
			case 0xdb: key_value=10;break;
			case 0xeb: key_value=14;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfb);//�ȴ������ɿ�	
	
	KEY_MATRIX_PORT=0xfd;//�������и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfd)//�жϵ����а����Ƿ���
	{
		delay_10us(1000);//����
		switch(KEY_MATRIX_PORT)//��������а������º�ļ�ֵ	
		{
			case 0x7d: key_value=3;break;
			case 0xbd: key_value=7;break;
			case 0xdd: key_value=11;break;
			case 0xed: key_value=15;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfd);//�ȴ������ɿ�	
	
	KEY_MATRIX_PORT=0xfe;//�������и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfe)//�жϵ����а����Ƿ���
	{
		delay_10us(1000);//����
		switch(KEY_MATRIX_PORT)//��������а������º�ļ�ֵ	
		{
			case 0x7e: key_value=4;break;
			case 0xbe: key_value=8;break;
			case 0xde: key_value=12;break;
			case 0xee: key_value=16;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfe);//�ȴ������ɿ�
	
	return key_value;		
}