#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "lidar.h"
#include "LCD.h"
#include "speaker.h"
#include "servo_controller.h"
#include "timers.h"


char Buffer[10];//LCD buffer


void main(void) {


  init_button();  //Initialization of all modules under button
  
  EnableInterrupts;
  
  
  
  for(;;){     //Permanent main loop
  
    sprintf(Buffer,"%.2f", GetDist()); //Load distance to buffer
    cmd2LCD(0x01);    //Clear LCD
    cmd2LCD(0x86);    //Go to top middle
    putsLCD(Buffer);  //Print buffer contents
    cmd2LCD(0xC6);    //Go to bottom middle
    
    if (GetDist() < 0.3){//Printing bottom contents and setting speaker tone depending on distance 
    
      PWMDTY01 = 56250;
      PWMPER01 = 56250;
      sprintf(Buffer,"Stop!");
      putsLCD(Buffer);   
              
    } 
    else if(GetDist()>1){
    
      PWMDTY01 = 0;
      PWMPER01 = 10; 
      
    }
    
    else if(GetDist()<1&&GetDist()>0.75){
    
      PWMDTY01 = 55000;
      PWMPER01 = 65000;   
      sprintf(Buffer,"Slow");
      putsLCD(Buffer);

      
    }
    else if(GetDist()<0.75&&GetDist()>0.5){
    
      PWMDTY01 = 45000;
      PWMPER01 = 55000;
      sprintf(Buffer,"Slow");
      putsLCD(Buffer);
      
    }
    else if(GetDist()<0.5&&GetDist()>0.3){
    
      PWMDTY01 = 35000;
      PWMPER01 = 45000;
      sprintf(Buffer,"Slow");
      putsLCD(Buffer);

      
    }
    /*    Alternate tones
    else if(GetDist()<1&&GetDist()>0.75){
    
      PWMDTY01 = 32500;
      PWMPER01 = 65000;   
      sprintf(Buffer,"Slow");
      putsLCD(Buffer);

      
    }
    else if(GetDist()<0.75&&GetDist()>0.5){
    
      PWMDTY01 = 23750;
      PWMPER01 = 47500;
      sprintf(Buffer,"Slow");
      putsLCD(Buffer);
      
    }
    else if(GetDist()<0.5&&GetDist()>0.3){
    
      PWMDTY01 = 15000;
      PWMPER01 = 30000;
      sprintf(Buffer,"Slow");
      putsLCD(Buffer);

      
    }
    */
    update_servo(); //Updates servo to next position, with a 0.5s delay
  }
  

	
	
	
	
for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}