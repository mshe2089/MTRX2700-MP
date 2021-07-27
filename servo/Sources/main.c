#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "servo_controller.h"



void main(void) {
  /* put your own code here */
  


	EnableInterrupts;
	
	servo_controller();


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
