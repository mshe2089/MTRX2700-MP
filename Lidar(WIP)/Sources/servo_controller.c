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
const int Xupper = 350; //With 375 representing a duty cycle of 180 degrees, inorder to not over stress the servo upper max was reduced by 20 units.
const int Xlower = 200; //With 187 representing a duty cycle of 0 degrees, inorder to not over stress the servo low min was increased by 20 units.
const int Yupper = 310; //It was found the centre of vertcial sweep was upshifted by 20 units in terms of duty cycle from 280. So the max vertical sweep point was made to be 10 units more.
const int Ylower = 290; //The minimum vertical sweep point was reduced by 10 points from the new centre found being 300.

//The "servo_controller" is responsble for intiallisingt he parameters for the PWM singnals of 6 and 7 which concantenated 
//and responsible for controlling.The horizontal sweeping servo. Also this function is responsible for intiallising the 
//parameters needed for the PWM signals of 4 and 5 which is responsible for controlling the veterical sweeping servo.
void servo_controller(void){
 
 PWMPOL|=0xA0; //1010 0000 The polarity of PWM7 and PWM3 is made to be high intiall low after the duty cycle has ended.
 PWMCTL|=0xCC; //1100 1100 PWM7 and 6 are concatenated, PWM5 and 4 are concatenated. Also PSWAI and PFRZ are enabled.
 PWMCAE|=0x00; //0000 0000 All pwms used will left alinged output.
 PWMPER7|=0b10100110; //PWM7 has period of 0.020 seconds,but has the lower bit from the calculation.
 PWMPER6|=0b00001110; //PWM6 has period of 0.020 seconds,but has the higher bit from the calculation.
 PWMPER5|=0b10100110; //PWM5 has period of 0.020 seconds,but has the lower bit from the calculation.
 PWMPER4|=0b00001110; //PWM4 has period of 0.020 seconds,but has the higher bit from the calculation.
 PWMPRCLK|=0x77; //0111 0111 The clock of A and B is prescaled down by a factor of 128
 //PWMSCLA = 0xFF; //0000 0000 The clock of A is scaled down a further by factor of 510.
 //PWMSCLB = 0xFF; //0000 0000 The clock of B is scaled down a further by factor of 510.
 PWMDTY67|= 200; //The duty cycle is set to 0.009sec, duty cycle value = period/(scale factor/clock freq)
 PWMDTY45|= 200; //The duty cycle is set to 0.009sec, duty cycle value = period/(scale factor/clock freq)
 PWMCLK|= 0x00; //0000 0000 The reason behind this is the Clock A and B will be used and not SA and SB for PWM7 and PWM3
 TSCR2|= 6;  //Clock is scaled by a factor of 64.
 TSCR1|=0x80; //1000 0000 Timer is enabled.
 PWME|=0xA0; //1010 0000  PWM67 and PWM45 are enabled.
 
 //PWMDTY67 = (Xupper + Xlower)/2;
 //PWMDTY45 = (Yupper + Ylower)/2;
 Xmode = 20; //Xmode increments  the horizontal sweeping servo motor's duty cycle by 20 units.
 Ymode = 10; //Ymode increments  the veterical sweeping servo motor's duty cycle by 10 units.
 
}


//The "update_servo" function is responsible for incrementing/decrememting the vertical sweep by 10 duty cycle units, as well as incrementing/decrementing the duty cycle 
//ofthe horizontal sweep by 20 units. This is done after readings of the lidar have been printed to the lcd and the speaker tone has been adjusted. The function justifies 
//if incrementing in the vertical or horizontal sweep needs to be converted to decrementing and vice versa, by assesing if the duty cycle surpasses the bound set by Ylower
//,Yupper, Xupper and Xlower.
void update_servo(void){

  
  if (PWMDTY67 >= Xupper){  //If the current duty cycle is greater than Xupper value, then the incrementing variable of Xmode will become negative inorder to make it decrement the servo's duty cycle.
      Xmode = -1 * Xmode;
  } else if (PWMDTY67 <= Xlower){  //If the current duty cycle is less than Xlower value, then the decrementing variable of Xmode will become positive inorder to make it increment the servo's duty cycle.
      Xmode = -1 * Xmode;
  }
  
  if (PWMDTY45 >= Yupper){  //If the current duty cycle is greater than Yupper value, then the incrementing variable of Ymode will become negative inorder to make it decrement the servo's duty cycle.
      Ymode = -1 * Ymode;
  } else if (PWMDTY45 <= Ylower){  //If the current duty cycle is greater than Ylower value, then the decrementing variable of Ymode will become negative inorder to make it increment the servo's duty cycle.
      Ymode = -1 * Ymode;
  }
 
    PWMDTY45 += Ymode; //The vertical sweeping servo is incremented/decremented by 10 units.
     delayby100ms();   //Then an delay of 200ms is put inplace  inorder to allow the servo to make its vertical adjustment before anything else happens.
     delayby100ms();   
  
     PWMDTY67 += Xmode; //The horizontal sweeping servo is incremented/decremented by 20 units.
     
     delayby100ms();    //Then a delay of 500ms is put inplace  inorder to allow the servo to make its horizontal adjustment before anything else happens.
     delayby100ms();
     delayby100ms();
     delayby100ms();
     delayby100ms();

  
}



  
