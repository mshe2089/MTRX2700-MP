#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "lidar.h"
#include "LCD.h"
#include "speaker.h"
#include "servo_controller.h"
#include "timers.h"


char Buffer[10];
int freq;


void main(void) {
  /* put your own code here */
  /*  
  Init_lidar(); 
  Init_speaker_PP3();
  openLCD();
  servo_controller();
  */
  init_button();
  
  EnableInterrupts;
  
  
  
  for(;;){ 
  
    sprintf(Buffer,"%.2f", GetDist());
    cmd2LCD(0x01);    //Clear LCD
    cmd2LCD(0x86);    //Go to top middle
    putsLCD(Buffer);  //Print buffer contents
    cmd2LCD(0xC6);    //Go to bottom middle
    if (GetDist() < 0.3){
        sprintf(Buffer,"Stop!");
        PWMDTY01 = 56250;
        PWMPER01 = 56250; 
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
    
    
    /*
    PWME_PWME3 = 1;   //beep start
    delaydowntime();  //wait depending on dist
    PWME_PWME3 = 0;   //beep stop
    delayuptime();  //wait depending on dist
    */
    
   
    update_servo();
  }
  

	
	
	
	
for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}