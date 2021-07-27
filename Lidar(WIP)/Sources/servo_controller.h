#ifndef SERVO_CONTROLLER_HEADER
#define SERVO_CONTROLLER_HEADER
#include "derivative.h"
#include "timers.h"

//The "servo_controller" is responsble for intiallisingt he parameters for the PWM singnals of 6 and 7 which concantenated 
//and responsible for controlling.The horizontal sweeping servo. Also this function is responsible for intiallising the 
//parameters needed for the PWM signals of 4 and 5 which is responsible for controlling the veterical sweeping servo.
void servo_controller(void);

//The "update_servo" function is responsible for incrementing/decrememting the vertical sweep by 10 duty cycle units, as well as incrementing/decrementing the duty cycle 
//ofthe horizontal sweep by 20 units. This is done after readings of the lidar have been printed to the lcd and the speaker tone has been adjusted. The function justifies 
//if incrementing in the vertical or horizontal sweep needs to be converted to decrementing and vice versa, by assesing if the duty cycle surpasses the bound set by Ylower
//,Yupper, Xupper and Xlower.
void update_servo(void);

#endif