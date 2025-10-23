/*******************************************************************************
�����Ƽ�

  File Name:       AD9851.h
  Author:          CHEN WEN PING
  Created:         2013/4/3
  Modified:		NO
  Revision: 		1.0
	 Address:			http://shop110336474.taobao.com/?spm=a230r.7195193.1997079397.1.DDyJvr
*********************************************************************************/
#ifndef _AD9851_H
#define _AD9851_H
#include "STC12C5A60S2.H"

sbit ad9851_w_clk    =P2^2;  //P2.2�ڽ�AD9851��w_clk��/PIN7
sbit ad9851_fq_up    =P2^1;  //P2.1�ڽ�AD9851��fq_up��/PIN8
sbit ad9851_rest     =P2^0;  //P2.0�ڽ�AD9851��rest��/PIN12
sbit ad9851_bit_data =P1^7;  //P1.7�ڽ�AD9851��D7��/PIN25
//P1Ϊ8λ���ݿ�
//***************************************************//
//              ad9851��λ(����ģʽ)                 //
//---------------------------------------------------//
void ad9851_reset();
void ad9851_reset_serial();
void ad9851_wr_parrel(unsigned char w0,double frequence);
void ad9851_wr_serial(unsigned char w0,double frequence);
void ad9851_wr_parrelnums(unsigned char w0,double frequence);


#endif