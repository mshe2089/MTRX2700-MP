// This header file and it's accompanying .c file is used to operate the speaker
#ifndef SPEAKER_HEADER
#define SPEAKER_HEADER

#include "derivative.h"
#include "timers.h"

//This "Init_speaker" module is responsible for intiallising the speaker beep tones. The systems requires
//The hardware nand gate inorder to operate where the output of PWM01 and PWM23 is compared 
//simultanoeusly inorder to produce an output which is connected to the speaker. The purpose of this
//setup is that PWM23 will serve as an almost constant high reference, inturn if the actual PWM which is altered
//being the concatenated channels of 01 with respect to the closet distance in which a surrounding obstacle
// is sensed by the lidar, inturn if that distance is greater than 1m the PWM01 will be made to be constanty low
//inturn the output of the and gate will also be low creating 0 speaker output.
void Init_speaker_PP3 (void); 


#endif