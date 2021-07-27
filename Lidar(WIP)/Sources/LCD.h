#ifndef LCD_HEADER
#define LCD_HEADER
#include "derivative.h"
#include "timers.h"


void openLCD(void);

void putsLCD (char *ptr);

void cmd2LCD (char cmd);

void delayby1s (void);

#endif