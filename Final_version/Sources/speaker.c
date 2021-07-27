#include "speaker.h"
#include "lidar.h"


// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


//This "Init_speaker" module is responsible for intiallising the speaker beep tones. The systems requires
//The hardware nand gate inorder to operate where the output of PWM01 and PWM23 is compared 
//simultanoeusly inorder to produce an output which is connected to the speaker. The purpose of this
//setup is that PWM23 will serve as an almost constant high reference, inturn if the actual PWM which is altered
//being the concatenated channels of 01 with respect to the closet distance in which a surrounding obstacle
// is sensed by the lidar, inturn if that distance is greater than 1m the PWM01 will be made to be constanty low
//inturn the output of the and gate will also be low creating 0 speaker output.
void Init_speaker_PP3 (void)
{
   PWMPOL   |= 0x0A; //0000 1010 The polarity of PWM3 is made to be high intially low after the duty cycle has ended.
   PWMCTL   |= 0x3C; //0011 1100 PWM2 and 3 are concatenated, PWM0 and 1 are concatenated. Also PSWAI and PFRZ are enabled.
   PWMCAE   |= 0x00; //0000 0000 All pwms used will left alinged output.
   PWMPRCLK |= 0x77; //0111 0111 The clock of A and B is prescaled down by a factor of 128.
   PWMPER23 = 50; //The concantenated PWM of 2 and 3, will approximately always remain high as it as frequency 3750Hz with a 50 percent duty cycle, to serve as refeence for the and gate, so when the PWM01 is ever made to be constantly low, inorder represent distance sensed is greater one meter is it will stop output to the speaker.
   PWMDTY23 = 25; //Duty cycle is equal to period inorder create a constant high signal.
   PWMCLK   |= 0x00; //0000 0000 The reason behind this is the Clock A and B will be used and not SA and SB for PWM01 and PWM23.
   
   TSCR2 |= 6;  //Clock is scaled by a factor of 64.
   TSCR1 |= 0x80; //1000 0000 Timer is enabled.
   
   PWMPER01 =  56250; //The period is made to 300ms.
   PWMDTY01 =  28125; //The duty cycle is to be half the period.
   
   PWME_PWME1 = 1; //The concantenated chanels of 01 is to be enabled.
   PWME_PWME3 = 1; //The concantenated chanels of 23 is to be enabled.
   
   
}