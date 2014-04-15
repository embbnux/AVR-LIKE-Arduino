/************************************************************
=============CopyRight of Embbnux  ==========================
==============Writer : Embbnux Ji============================
==============avr 串口   驱动程序 ============================
==============http://www.embbnux.com ========================
==============avr 串口 驱动程序 ============================
==============ATmega16 16MHZ ================================
**************************************************************/
#ifndef USART_H_H
#define USART_H_H

#define BAUD 9600
#define CRYSTAL 16000000 //晶振

extern void USART_Init( void );
// 数据发送【发送5 到8 位数据位的帧】
extern void USART_Transmit( unsigned char data );
// 数据接收【以5 到8 个数据位的方式接收数 据帧】
extern unsigned char USART_Receive( void );
extern void USART_SEND_String(char *str);
#endif

[/css]
