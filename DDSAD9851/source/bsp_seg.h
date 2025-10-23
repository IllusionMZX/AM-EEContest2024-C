#include "STC12C5A60S2.H"
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

void delay_10us(unsigned int ten_us);
void Seg_Tran(unsigned char *seg_string, unsigned char *seg_buf);
void Seg_Disp(unsigned char *seg_buf);

	