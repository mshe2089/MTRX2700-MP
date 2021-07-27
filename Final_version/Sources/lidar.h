// This header file and it's accompanying .c file is used to operate the 
// lidar on the pan-tilt unit. It operates by reading a PWM signal from 
// timer channel 1 and converting the values to meters
#ifndef LIDAR_HEADER
#define LIDAR_HEADER

#include "derivative.h"
#include "timers.h"


// Lidar startup
void Init_lidar (void);

// Returns the calculated distance 
double GetDist (void);

// Lidar interrupt definition
__interrupt void IOC1_ISR(void);

#endif