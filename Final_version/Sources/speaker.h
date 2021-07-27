// This header file and it's accompanying .c file is used to operate the speaker
#ifndef SPEAKER_HEADER
#define SPEAKER_HEADER

#include "derivative.h"
#include "timers.h"

// Initialises pwm3 and pwm1 to play a frequency. pwm3 determines tone, pwm1 determines beep rate
void Init_speaker_PP3 (void); 


#endif