// Code was taken from Han-Way Huang. HC12/9S12 An Introduction to Software and 
// Hardware Interfacing. 2 ed., Delmar, 2010, USA. Page 336



#include "LCD.h"
#include "derivative.h"

#define LCD_DAT PORTK // Port K drives LCD data pins, E, and RS
#define LCD_DIR DDRK // Direction of LCD port
#define LCD_E 0x02 // E signal
#define LCD_RS 0x01 // RS signal
#define LCD_E_RS 0x03 // assert both E and RS signals


  
void cmd2LCD (char cmd)
{
 char temp;
 temp = cmd; // save a copy of the command
 cmd &= 0xF0; // clear out the lower 4 bits
 LCD_DAT &= (~LCD_RS); // select LCD instruction register
 LCD_DAT |= LCD_E; // pull E signal to high
 cmd >>= 2; // shift to match LCD data pins
 LCD_DAT = cmd | LCD_E; // output upper 4 bits, E, and RS
 asm ("nop"); // dummy statements to lengthen E
 asm ("nop"); // 
 asm ("nop");
 LCD_DAT &= (~LCD_E); // pull E signal to low
 cmd = temp & 0x0F; // extract the lower 4 bits
 LCD_DAT |= LCD_E; // pull E to high
 cmd <<= 2; // shift to match LCD data pins
 LCD_DAT = cmd | LCD_E; // output upper 4 bits, E, and RS
 asm("nop"); // dummy statements to lengthen E
 asm("nop"); // “
 asm("nop");
 LCD_DAT &= (~LCD_E); // pull E-clock to low
 //delayby50us(); // wait until the command is complete
 delayby1ms();
 delayby1ms();
 delayby1ms();
}

void openLCD(void)
{
 int i;
 LCD_DIR = 0xFF; // configure LCD_DAT port for output
 
 for (i = 0; i < 100; i++){
    delayby1ms();
 }
 cmd2LCD(0x28); // set 4-bit data, 2-line display, 537 font
 cmd2LCD(0x0F); // turn on display, cursor, blinking
 cmd2LCD(0x06); // move cursor right
 cmd2LCD(0x01); // clear screen, move cursor to home
 //delayby1ms(); // wait until clear display command is complete
 //delayby1ms();
 delayby1ms();
 delayby1ms();
 delayby1ms();
}

void putcLCD(char cx)
{
 char temp;
 temp = cx;
 LCD_DAT |= LCD_RS; // select LCD data register
 LCD_DAT |= LCD_E; // pull E signal to high
 cx &= 0xF0; // clear the lower 4 bits
 cx >>= 2; // shift to match the LCD data pins
 LCD_DAT = cx|LCD_E_RS; // output upper 4 bits, E, and RS
 asm("nop"); // dummy statements to lengthen E
 asm("nop"); // “
 asm("nop");
 LCD_DAT &= (~LCD_E); // pull E to low
 cx = temp & 0x0F; // get the lower 4 bits
 LCD_DAT |= LCD_E; // pull E to high
 cx <<= 2; // shift to match the LCD data pins
 LCD_DAT = cx|LCD_E_RS; // output lower 4 bits, E, and RS
 asm("nop"); // dummy statements to lengthen E
 asm("nop"); // “
 asm("nop");
 LCD_DAT &= (~LCD_E); // pull E to low
 //delayby50us();
 delayby1ms();
}

void putsLCD (char *ptr)
{
 while (*ptr) {
  putcLCD(*ptr);
  ptr++;
 }
}