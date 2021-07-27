#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
 /* common defines and macros */
#include "derivative.h"
#include <time.h>
#include "servo_controller.h"

int Xmode;
int Ymode;
const int Xupper = 350;
const int Xlower = 200;
const int Yupper = 310;
const int Ylower = 290;

void servo_controller(void){
  volatile int breakout;
  volatile unsigned int TCNT_post; //This stores the timer count after the operation.
  volatile unsigned int TCNT_prev; //This stores the timer count before the operation.
  volatile signed int TCNT_result;
  int i;
 
 
 

 
 
 PWMPOL|=0xA0; //1010 0000 The polarity of PWM7 and PWM3 is made to be high intiall low after the duty cycle has ended.
 PWMCTL|=0xCC; //1100 1100 PWM7 and 6 are concatenated, PWM5 and 4 are concatenated. Also PSWAI and PFRZ are enabled.
 PWMCAE|=0x00; //0000 0000 All pwms used will left alinged output.
 PWMPER7|=0b10100110; //PWM7 has period of 0.220 seconds,  PWMPER7 =
 PWMPER6|=0b00001110;
 PWMPER5|=0b10100110; //PWM5 has period of 0.220 seconds,
 PWMPER4|=0b00001110;
 PWMPRCLK|=0x77; //0111 0111 The clock of A and B is prescaled down by a factor of 128
 //PWMSCLA = 0xFF; //0000 0000 The clock of A is scaled down a further by factor of 510.
 //PWMSCLB = 0xFF; //0000 0000 The clock of B is scaled down a further by factor of 510.
 PWMDTY67|= 200; //The duty cycle is set to 0.009sec, duty cycle value = period/(scale factor/clock freq)
 PWMDTY45|= 200; //The duty cycle is set to 0.020seconds, duty cycle value = period/(scale factor/clock freq)
 PWMCLK|= 0x00; //0000 0000 The reason behind this is the Clock A and B will be used and not SA and SB for PWM7 and PWM3
 
 TSCR2|= 6;  //Clock is scaled by a factor of 64.
 TSCR1|=0x80; //1000 0000 Timer is enabled.
 PWME|=0xA0; //1010 0000  pwm 7 and 5 are enabled.
 
 PWMDTY67 = (Xupper + Xlower)/2;
 PWMDTY45 = (Yupper + Ylower)/2;
 Xmode = 20; //Y increments
 Ymode = 10; //X increments
 
}
 
 
void update_servo(void){


  if (PWMDTY67 >= Xupper){
      Xmode = -1 * Xmode;
  } else if (PWMDTY67 <= Xlower){
      Xmode = -1 * Xmode;
  }
  
  if (PWMDTY45 >= Yupper){
      Ymode = -1 * Ymode;
  } else if (PWMDTY45 <= Ylower){
      Ymode = -1 * Ymode;
  }
 
    PWMDTY45 += Ymode;
     delayby100ms();
     delayby100ms();
  
     PWMDTY67 += Xmode;
     delayby100ms();
     delayby100ms();
     delayby100ms();

  
}



  
