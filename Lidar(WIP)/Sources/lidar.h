#ifndef LIDAR_HEADER
#define LIDAR_HEADER

#include "derivative.h"
#include "timers.h"


// Lidar startup
void Init_lidar (void);

void delayuptime(void);

void delaydowntime(void);

double GetDist (void);

// Lidar interrupt definition
__interrupt void IOC1_ISR(void);


__interrupt void TOF_ISR(void);


#endif