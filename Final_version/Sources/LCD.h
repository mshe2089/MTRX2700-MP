// This header file and it's accompanying .c file is used to operate the
// LCD

// Code was taken from Han-Way Huang. HC12/9S12 An Introduction to Software and 
// Hardware Interfacing. 2 ed., Delmar, 2010, USA. Page 336

#ifndef LCD_HEADER
#define LCD_HEADER
#include "derivative.h"
#include "timers.h"

// Switches on the LCD
void openLCD(void);

// Prints buffer to LCD
void putsLCD (char *ptr);

// Send command to LCD
void cmd2LCD (char cmd);

#endif