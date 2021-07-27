#include "lidar.h"
#include "LCD.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


volatile word edge_time_1;
volatile word edge_time_2;

double distance = 0;
int can_read = 1;  
double distance_copy;                 
                    
                    
void Init_lidar (void){
   //timer   
   TSCR1 = 0x90;  // enable timer , fastflag clear
   TSCR2 = 0x06;  // prescaler 64 , no overflow interrupts
   TIE   = 0x02;  // enable timer interrupt for channel 1
   
   //enhanced capture
   TCTL3 = 0x00;  
   TCTL4 = 0x04;  // enable capture on any edge for timer channel 1
   TIOS  = 0x00;  //enable input capture   
}


double GetDist (void){
   return distance;
}


word input_capture(void){
   word time = TCNT;  // storing value in timer count register into a variable  (see timer module p26)
   return time;
}


double compare_time(word t1, word t2){
 double dist;
 word timer_diff = t2 - t1;  // taking the difference in timer values
 
 // each clock cycle takes 2.66 microseconds and the counter takes 174ms to overflow
 if (t2 < t1){
    dist = ((double)timer_diff*0.00000266 + 0.174) * 1000;
 } else {
    dist = ((double)timer_diff*0.00000266) * 1000;
 }
 
 
 return dist; 
}




#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void IOC1_ISR(void) { 
 
  if (TCTL4 == 0x04){ //if rising edge captured
    edge_time_1 = TC1;
    can_read = 0;       //disallow dist reads   --UNUSED--
    
    //TFLG1_C1F = 1;      //flag reset
    TCTL4 = 0x08;       //enable falling captures
  } 
  
  else if (TCTL4 == 0x08){ //if falling edge captured
    edge_time_2 = TC1;
    distance = compare_time(edge_time_1, edge_time_2);
    can_read = 1;       //allow dist reads      --UNUSED--
    
    //TFLG1_C1F = 1;      //flag reset
    TCTL4 = 0x04;       //enable rising edge capture
    
  }  
  
}

