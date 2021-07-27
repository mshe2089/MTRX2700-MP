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
    
    if (GetDist() < 0.3){//This if statment is satisfied if the lidar senses something within 0.3m. 
    
      PWMDTY01 = 56250;  //Constant tone is then outputed from the speaker. As the duty cycle occurs for the whole period of the PWM signal.
      PWMPER01 = 56250;
      sprintf(Buffer,"Stop!"); //Stop is presented on the LCD display.
      putsLCD(Buffer);   
              
    } 
    else if(GetDist()>1){//This if statment is satisfied if the lidar senses something over 1m. 
    
      PWMDTY01 = 0; //There will be no speaker output, as the duty cycle is set to zero.
      PWMPER01 = 10; 
      
    }
    
    else if(GetDist()<1&&GetDist()>0.75){//This if statment is satisfied if the lidar senses something within a range of 0.75 to 1m. 
    
      PWMDTY01 = 55000;   //The tone created is 2.9Hz signal with a 85% duty cycle.
      PWMPER01 = 65000;   
      sprintf(Buffer,"Slow"); //The term Slow is printed to the lcd screen.
      putsLCD(Buffer);

      
    }
    else if(GetDist()<0.75&&GetDist()>0.5){//This if statment is statisfied if the lidar senses something within a range of 0.5 amd 0.75m
    
      PWMDTY01 = 45000;  //The tone will then get faster as the pwm signal becomes 3.4Hz, with a 82% duty cycle
      PWMPER01 = 55000;
      sprintf(Buffer,"Slow"); //The term Slow is printed to the lcd screen.
      putsLCD(Buffer);
      
    }
    else if(GetDist()<0.5&&GetDist()>0.3){//This if statment is satisfied if the lidar senses something within a range of 0.3 and 0.5m
    
      PWMDTY01 = 35000; //The tone will then get faster as the pwm signal becomes 4.2Hz, with a 78% duty cycle
      PWMPER01 = 45000;
      sprintf(Buffer,"Slow"); //The term Slow is printed to the lcd screen.
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