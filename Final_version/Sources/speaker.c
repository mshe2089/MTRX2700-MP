#include "speaker.h"
#include "lidar.h"


// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


//Generates a PWM that give the speaker its beep tone
void Init_speaker_PP3 (void)
{
   PWMPOL   |= 0x0A; //0000 1010 The polarity of PWM3 is made to be high intiall low after the duty cycle has ended.
   PWMCTL   |= 0x3C; //0011 1100 PWM2 and 3 are concatenated, PWM5 and 4 are concatenated. Also PSWAI and PFRZ are enabled. why?
   PWMCAE   |= 0x00; //0000 0000 All pwms used will left alinged output.
   PWMPRCLK |= 0x77; //0111 0111 The clock of A and B is prescaled down by a factor of 128
   //PWMSCLA = 0xFF; //0000 0000 The clock of A is scaled down a further by factor of 510.
   //PWMSCLB = 0xFF; //0000 0000 The clock of B is scaled down a further by factor of 510.
   PWMPER23 = 50; 
   PWMDTY23 = 25; //The duty cycle is set to 0.009sec, duty cycle value = period/(scale factor/clock freq);
   PWMCLK   |= 0x00; //0000 0000 The reason behind this is the Clock A and B will be used and not SA and SB for PWM7 and PWM3
   
   TSCR2 |= 6;  //Clock is scaled by a factor of 64.
   TSCR1 |= 0x80; //1000 0000 Timer is enabled.
   
   PWMPER01 =  56250;
   PWMDTY01 =  28125;
   
   PWME_PWME1 = 1;
   PWME_PWME3 = 1;
   
   
}