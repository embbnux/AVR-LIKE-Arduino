/******************************************************************************************
=====================CopyRight of Embbnux Ji ===================================================
=====================Writer : Embbnux  Ji    ===================================================
=====================http://www.embbnux.com  ===================================================
=====================avr 1602_lcd驱动程序 ===================================================
=====================ATmega16 16MHZ       ===================================================
******************************************************************************************/
#include <avr/io.h>
#include "Delay.h"
//#include "usart.h"
//   /usr/lib/avr/include/
#include "driver_1602.h"
//void Delayus(uint US);
//void Delayms(uint MS);
unsigned char num_table[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
/***********lcd test***************
void main(void){
   unsigned char display[]={"  LCD1602 TEST  "};
   unsigned char display1[]={"  Writor: JYC  "};
   unsigned char tmp;
   unsigned int i=0;
   USART_Init();
   LCD_init();
   Delay_nMS(500);
   USART_SEND_String("\nLCD INIT OK");
   while(1){
      //LCD_init();
     // LCD_init();
      //if(UCSRA&(1<<RXC))
     Delay_nMS(500);
	  //set_LCD_xy(0,0);
	  //USART_SEND_String("LCD START");
      LCD_write_string(0,0,display);
      Delay_nMS(50);
      LCD_write_string(0,1,display1);
	  //LCD_write_onechar(0,'A');
	  //Delay_nMS(2000);
      USART_SEND_String("\nLCD OK");
      Delay_nMS(1000);
      set_LCD_xy(0,0);
     while(1){
       if(UCSRA&(1<<RXC)){
          tmp=USART_Receive();
          LCD_write_onechar(0,tmp);
          USART_Transmit(tmp);
          i++;
          if (i==16)
             set_LCD_xy(0,1);
          if (i==32){
	     set_LCD_xy(0,0);
	     i=0;	
          }
            
       }
     }
   }
}

**********************************/
//lcd初始化
void LCD_init(void)
{   
    LCD_DATA_PORT=0xf0;
    LCD_DATA_POUT;
    LCD_EN_1;
    LCD_RW_1;
    LCD_RS_1;
    LCD_Control_IN;
	
     Delay_nMS(15 );
    LCD_DATA_POUT;     
    LCD_Control_OUT;
    //LCD_RS_0;
    LCD_write_onechar(0x38,0);
	Delay_1MS( );
    LCD_write_onechar(0x38,0);
	Delay_1MS( );
    LCD_write_onechar(0x38,0);
	Delay_1MS( );
    LCD_write_onechar(0x38,0); //功能设置
    LCD_write_onechar(0x08,0);    /*显示关闭*/
    LCD_write_onechar(0x01,0);    /*显示清屏*/
    LCD_write_onechar(0x06,0);    /*显示光标移动设置*/
	Delay_1MS( );
    LCD_write_onechar(0x0C,0);    /*显示开及光标设置*/
}
//清屏
void LCD_clean(){

   LCD_write_onechar(0x01,0);

}
//关屏
void LCD_close(){
   LCD_write_onechar(0x08,0);
}
// en端口产生一个脉冲，写LCD
void LCD_en_write(void)        
{
    LCD_EN_1;
    Delay_nUS(300);  //E脉冲周期最小150us
    LCD_EN_0;
}

//判断LCD忙标志
void wait_LCD_Ready(void)
{
    unsigned char temp1;
    LCD_DATA_PORT =0XFF;
    LCD_DATA_PIN;                  //D7设为输入，准备判断LCD忙标志 
                                   //1为忙  0为空闲
	LCD_RS_0;
    LCD_RW_1;                      //读
	LCD_EN_1;
	Delay_nUS(2);
    while((temp1=PINC & 0X80));
	LCD_EN_0;
    LCD_RS_1;
	LCD_DATA_POUT;
}

//写一个字节到LCD ,COMM(指令)   DAT（显示数据)
void LCD_write_onechar(unsigned char COMM,unsigned char DAT)
{ 
	 wait_LCD_Ready();         //等待LCD空闲
	 LCD_RW_0;                 //写
	 
	 //写数据
	 if(COMM==0)
	 {
	    LCD_RS_1;  //RS高电平向LCD写数据
		LCD_DATA_PORT=DAT;
	 } 
	 //写命令
	 else
	 {
	    LCD_RS_0;
        LCD_DATA_PORT=COMM;
	 }
	 LCD_en_write(); 
	 Delay_nUS(2);
	 LCD_RW_1;
	 LCD_RS_1;
}

//LCD字符串显示函数 x/y（X与Y坐标)   *string（字符串首地址)
void LCD_write_string(unsigned char X,unsigned char Y,unsigned char *string)
{
    set_LCD_xy( X, Y );                //设置LCD显示坐标
    while (*string) 
    {
      LCD_write_onechar(0,*string );
	  string ++;                       //指向下一显示字符地址
    }
}
 
//设置显示坐标 x/y（X与Y坐标) 
void set_LCD_xy(unsigned char x, unsigned char y )
{
    unsigned char DIS_address;
    if (y == 0) 
	   DIS_address = 0X80+x;            //第一行X列
    else 
       DIS_address = 0xC0 + x;
    LCD_write_onechar( DIS_address, 0 );  //第二行X列
} 
//把整型数转化为字符串
void int_to_char (unsigned int num,unsigned char * string){
   unsigned int temp[2];
   unsigned char char_temp[4];

   temp[0] = num /256;
   temp[1] = num %256;
   char_temp[0] = temp[0]/16;
   char_temp[1] = temp[0]%16;
   char_temp[2] = temp[1]/16;
   char_temp[3] = temp[1]%16;
   string[2] = num_table[char_temp[0]];
   string[3] = num_table[char_temp[1]];
   string[4] = num_table[char_temp[2]];
   string[5] = num_table[char_temp[3]];
   //string[6] = 0;

}

void LCD_write_int(unsigned char X,unsigned char Y,unsigned int num){
    unsigned char *string="0X0000";
    int_to_char(num,string);
    LCD_write_string(X,Y,string);
   
}
/*
 ///延时函数
void Delayus(uint US)		  
{
     uint i;
     US=US*5/4;	  	 
     for( i=0;i<US;i++); 
}

void Delayms(uint MS)		  
{
     uint i,j;
     for( i=0;i<MS;i++)
     for(j=0;j<1141;j++);
}

*/





