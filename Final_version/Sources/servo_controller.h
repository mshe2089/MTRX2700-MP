// Module for controlling the servo
#ifndef SERVO_CONTROLLER_HEADER
#define SERVO_CONTROLLER_HEADER
#include "derivative.h"
#include "timers.h"

// Initiates the servo
void servo_controller(void);

// Updates the position of the servo by defined increment
void update_servo(void);

#endif