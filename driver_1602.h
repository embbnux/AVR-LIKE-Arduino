/******************************************************************************************
=====================CopyRight of Embbnux Ji ===================================================
=====================Writer : Embbnux  Ji    ===================================================
=====================http://www.embbnux.com  ===================================================
=====================avr 1602_lcd驱动程序 ===================================================
=====================ATmega16 16MHZ       ===================================================
******************************************************************************************/
#ifndef DRIVER_1602_H_H_
#define DRIVER_1602_H_H_
  
# include <avr/io.h>

#define  LCD_DATA_PORT    PORTC        //定义LCD的D0-D7所在端口
#define  LCD_DATA_POUT    DDRC=0xFF    //定义LCD数据端口为输出
#define  LCD_DATA_PIN     DDRC=0x00    //定义LCD数据端口为输入(在读LCD状态时用到)

#define  LCD_Control_PORT PORTB        //定义LCD的EN RW RS所在端口
#define  LCD_Control_OUT  DDRB|=(1<<DDB5)|(1<<DDB6)|(1<<DDB7)
#define  LCD_Control_IN   DDRB&=~((1<<DDB5)|(1<<DDB6)|(1<<DDB7))

#define  LCD_EN_1         PORTB|=1<<PB5
#define  LCD_EN_0         PORTB&=~(1<<PB5)
//LCD读写控制引脚
#define  LCD_RW_1         PORTB|=1<<PB6
#define  LCD_RW_0         PORTB&=~(1<<PB6)
//LCD指令或数据选择引脚
#define  LCD_RS_1         PORTB|=1<<PB7
#define  LCD_RS_0         PORTB&=~(1<<PB7)

extern void LCD_init(void);
extern void mcu_init(void);
extern void LCD_en_write(void);
extern void wait_LCD_Ready(void);

extern void set_LCD_xy(unsigned char x, unsigned char y );
extern void LCD_write_onechar(unsigned char COMM,unsigned char DAT);
extern void LCD_write_string(unsigned char X,unsigned char Y,unsigned char *string);
extern void LCD_close();
extern void LCD_clean();
extern void LCD_write_int(unsigned char X,unsigned char Y,unsigned int num);
extern void int_to_char (unsigned int num,unsigned char * string);
#endif
