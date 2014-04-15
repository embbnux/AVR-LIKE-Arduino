/************************************************************
=============CopyRight of Embbnux  ==========================
==============Writer : Embbnux Ji============================
==============avr 串口   驱动程序 ============================
==============http://www.embbnux.com ========================
==============avr 串口 驱动程序 ============================
==============ATmega16 16MHZ ================================
**************************************************************/
#include <avr/io.h>
//#include <macros.h>

//初始化
void USART_Init( void ){
   UBRRL = 25;//    38400
   UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
  
   UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
      
}

//发送
void USART_Transmit( unsigned char data ){
    
     while ( !( UCSRA & (1<<UDRE)) );
    
     UDR = data;
}

void USART_SEND_String(char *str){
    while(*str)
	{
	  USART_Transmit(*str) ;
	  str++;
	}
}

//接收信息
unsigned char USART_Receive( void ){
     
    while ( !(UCSRA & (1<<RXC)) );
    
    return UDR;
}
