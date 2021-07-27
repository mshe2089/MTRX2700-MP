#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include "derivative.h"

// set button to not be in reverse mode
void init_button(void);

// code to enter reverse mode
void enter_reverse_mode(void);

// exit reverse mode
void exit_reverse_mode(void);

// Interrupt for button
__interrupt void PH0_ISR(void);


#endif