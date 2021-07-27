#include "button.h"

// flag to signal whether in reverse mode                        
int reverse_flag;


void init_button(void){
  PIEH = 0x01;      // enable interrupt for PH0
  DDRH = 0x00;      // set PH0 to input
  PPSH = 0x01;      // set pull down/ pull up mode for PH0
  PPSH = 0x01;      // set interrupt to trigger on rising edge
  PIFH = 0x01;      // clear interrupt flag
  reverse_flag = 0; // Clearing reverse flag 
}

void enter_reverse_mode(void){
  PPSH = 0x00;      // set interrupt to trigger on falling edge
  PIFH = 0x01;      // clear interrupt flag 
  reverse_flag = 1; // setting reverse flag
}

void exit_reverse_mode(void){
  PPSH = 0x01;      // set interrupt to trigger on rising edge
  PIFH = 0x01;      // clear interrupt flag
  reverse_flag = 0; // Clearing reverse flag 
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
  __interrupt void PH0_ISR(void) { 
    
    // enter reverse mode if not in reverse mode
    if (reverse_flag == 0){
     enter_reverse_mode(); 
    } else if (reverse_flag == 1){
     exit_reverse_mode(); 
    } 
  }




