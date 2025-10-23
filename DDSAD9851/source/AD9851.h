/*******************************************************************************
康威科技

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

sbit ad9851_w_clk    =P2^2;  //P2.2口接AD9851的w_clk脚/PIN7
sbit ad9851_fq_up    =P2^1;  //P2.1口接AD9851的fq_up脚/PIN8
sbit ad9851_rest     =P2^0;  //P2.0口接AD9851的rest脚/PIN12
sbit ad9851_bit_data =P1^7;  //P1.7口接AD9851的D7脚/PIN25
//P1为8位数据口
//***************************************************//
//              ad9851复位(并口模式)                 //
//---------------------------------------------------//
void ad9851_reset();
void ad9851_reset_serial();
void ad9851_wr_parrel(unsigned char w0,double frequence);
void ad9851_wr_serial(unsigned char w0,double frequence);
void ad9851_wr_parrelnums(unsigned char w0,double frequence);


#endif