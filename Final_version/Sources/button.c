#include "button.h"
#include "lidar.h"
#include "LCD.h"
#include "speaker.h"
#include "servo_controller.h"
#define LCD_DIR DDRK // Direction of LCD port



// flag to signal whether in reverse mode                        
int reverse_flag;


void init_button(void){
  PIEH = 0x01;      // enable interrupt for PH0
  DDRH = 0x00;      // set PH0 to input
  PPSH = 0x01;      // set pull down/ pull up mode for PH0
  PIFH = 0x01;      // clear interrupt flag
  if(PTIH_PTIH0 == 0){
    reverse_flag = 0; // Clearing reverse flag 
    PPSH = 0x01;      // set interrupt to trigger on rising edge
  }else if (PTIH_PTIH0 == 1){
    reverse_flag = 1; 
    PPSH = 0x00;      // set interrupt to trigger on falling edge
    Init_lidar(); 
    Init_speaker_PP3();
    openLCD();
    servo_controller();
  }
  
}

void enter_reverse_mode(void){
  PPSH = 0x00;      // set interrupt to trigger on falling edge
  PIFH = 0x01;      // clear interrupt flag 
  reverse_flag = 1; // setting reverse flag
  Init_lidar(); 
  Init_speaker_PP3();
  openLCD();
  servo_controller();
}

void exit_reverse_mode(void){
  PPSH = 0x01;      // set interrupt to trigger on rising edge
  PIFH = 0x01;      // clear interrupt flag
  reverse_flag = 0; // Clearing reverse flag 
  LCD_DIR = 0x00; // turns of LCD_DAT
  TSCR1 = 0x00;  // disable timer to disable lidar and speaker
  PWME =0x00; //1010 0000  pwm 7 and 5 are disabled. Turns off servo
   PWME_PWME1 = 0;
   PWME_PWME3 = 0;
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




