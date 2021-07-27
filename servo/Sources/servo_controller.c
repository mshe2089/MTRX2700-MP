#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
 /* common defines and macros */
#include "derivative.h"
#include <time.h>
#include "servo_controller.h"

void delayby1ms(void){     //simple delay  using loop
  float o1;
  int i;
  o1 = 999;
  for (i = 0; i < 2000; i++){
      o1*10;
  }
}

void delayby10ms(void){     //simple delay  using loop
  int i;
  for (i = 0; i < 10; i++){
      delayby1ms();
  }
}

void delayby100ms(void){     //simple delay  using loop
  int i;
  for (i = 0; i < 100; i++){
      delayby1ms();
  }
}

void servo_controller(void){
  volatile int breakout;
  volatile unsigned int TCNT_post; //This stores the timer count after the operation.
  volatile unsigned int TCNT_prev; //This stores the timer count before the operation.
  volatile signed int TCNT_result;
  int i;
 
 
 

 
 
 PWMPOL=0xA0; //1010 0000 The polarity of PWM7 and PWM3 is made to be high intiall low after the duty cycle has ended.
 PWMCTL=0xCC; //1100 1100 PWM7 and 6 are concatenated, PWM5 and 4 are concatenated. Also PSWAI and PFRZ are enabled.
 PWMCAE=0x00; //0000 0000 All pwms used will left alinged output.
 PWMPER7=0b10100110; //PWM7 has period of 0.220 seconds,  PWMPER7 =
 PWMPER6 = 0b00001110;
 PWMPER5=3750; //PWM5 has period of 0.220 seconds, 
 PWMPRCLK =0x77; //0111 0111 The clock of A and B is prescaled down by a factor of 128
 //PWMSCLA = 0xFF; //0000 0000 The clock of A is scaled down a further by factor of 510.
 //PWMSCLB = 0xFF; //0000 0000 The clock of B is scaled down a further by factor of 510.
 PWMDTY67 = 200; //The duty cycle is set to 0.009sec, duty cycle value = period/(scale factor/clock freq)
 PWMDTY5=0b11111010; //The duty cycle is set to 0.020seconds, duty cycle value = period/(scale factor/clock freq)
 PWMDTY4=0b00000000;
 PWMCLK= 0x00; //0000 0000 The reason behind this is the Clock A and B will be used and not SA and SB for PWM7 and PWM3
 
 TSCR2 = 6;  //Clock is scaled by a factor of 64.
 TSCR1 =0x80; //1000 0000 Timer is enabled.
 PWME =0x80; //1010 0000  pwm 7 and 5 are enabled.
 
 
 while(PWMDTY67<350){ 
 
    delayby100ms();
    
    PWMDTY67=PWMDTY67+ 1; 
    
 }

 
  while(PWMDTY67>200){
   
    delayby10ms();
     
    PWMDTY67=PWMDTY67- 1;     
  }
  
  while(PWMDTY67<350){ 
 
    delayby1ms();
    
    PWMDTY67=PWMDTY67+ 1; 
    
 }
 
  while(PWMDTY67>200){
   
    delayby1ms();
     
    PWMDTY67=PWMDTY67- 1;     
  }
  
  while(PWMDTY67<350){ 
 
    delayby1ms();
    
    PWMDTY67=PWMDTY67+ 1; 
    
 }
 
  while(PWMDTY67>200){
   
    delayby1ms();
     
    PWMDTY67=PWMDTY67- 1;     
  }
  
  while(PWMDTY67<350){ 
 
    delayby1ms();
    
    PWMDTY67=PWMDTY67+ 1; 
    
 }
 
  while(PWMDTY67>200){
   
    delayby1ms();
     
    PWMDTY67=PWMDTY67- 1;     
  }
  
 
}



  
