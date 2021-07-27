#include "timers.h"

#include "derivative.h"      /* derivative-specific definitions */

void delayby1ms(void){     //simple delay  using loop
  float o1;      //mathematical operation loop
  int i;
  o1 = 999;
  for (i = 0; i < 2000; i++){
      o1*10;
  }
}

void delayby1s(void){     //simple delay using loop
  int i;
  for (i = 0; i < 1000; i++){
      delayby1ms();
  }
}

void delayby10ms(void){     //simple delay using loop
  int i;
  for (i = 0; i < 10; i++){
      delayby1ms();
  }
}

void delayby100ms(void){     //simple delay using loop
  int i;
  for (i = 0; i < 100; i++){
      delayby1ms();
  }
}
