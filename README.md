# MTRX2700-major
**Authors** - 
Jan Lum - LIDAR, button

Daniel Shen - LIDAR, speaker, LCD

Travis Giannarakis - Servo, speaker

## Introduction of the System:
The purpose of this system is to aid people who are bound to wheelchairs with limited neck movement.
The device is placed on the back of the wheelchair facing behind the user. It is then operated
through the use of a switch. When the switch is pulled high, the device will enter reverse mode. 
The LIDAR on the device will be used to detect and measure objects within the line of sight of the 
laser. The servo will be used to oscillate the LIDAR to increase the detection range of the sensor.
The distance of the nearest object detected by the LIDAR will be displayed on the LCD. The speaker 
will play sounds at different speeds depending on the distance of the object as a warning to the user.

## Instruction for running the system:
To run the system the code is ran, but you must flick the dip switch of PH0, it will then engage the program. Where an object detected greater than one meter away the distance reading is only printed to screen. If you within one meter but greater than 0.3m, the slow and the distance reading will be printed to the screen. Finally if the object or surrounding being sense is within 0.3m the message of stop and current distance measurment is printed to the screen. Also within one meter the beeping tone will turn on, increasing in frequency as object or suroudning gets closer to the wheelchair. Within 0.3m the beeping tone becomes ones solid tone. To turn the program off flick the switch again, vice versa.

## Module overview:

##### -LCD.c

The LCD module handles all processes relating to the HD44780U LCD.
Within this system the LCD is programmed to display lidar distance information and a warning message accordingly.

The LCD is initialized using **openLCD**.
Null terminated strings can sent to the LCD and displayed with **puts2LCD**.
Clearing, cursor movements and other functionalities are performed by sending instruction sets with **cmd2LCD**. Refer to HD44780U datasheet for details.

```c
void openLCD(void); //Initializes LCD, call on activation

void putsLCD(char* S); //Outputs a null-terminated string S to LCD

void cmd2LCD(char cmd); //Output instruction set byte cmd to LCD
```

##### -lidar.c

The Lidar module measures PWM pulse width transmitted from the LIDAR-Lite v2. It is connected to PT1 on cont trigger and uses interrupts to track time. 
Within this system it is used to track the proximity of nearby obstacles.

There is no functionality to trigger on PH0; the Lidar unit is presumed to be in continuous trigger mode.
Any accompanying module that uses interrupts must halt the timer or disable PT1 interrupts upon interrupt to prevent distance calculation errors.

The Lidar is initialized using **Init_lidar**.
The last lidar measurement taken, in meters, can be acquired using **GetDist**.

```c
void Init_lidar(void); //Initializes Lidar, call on activation

double GetDist(void); //Returns last distance measurement in meters
```

##### -speaker.c

The Speaker module initializes two PWM signals used to drive the on board speaker. Being the concantenated PWM signal of PWM01 which will be used as the pwm signal that will be
be adjusted based on the closes of the surroundings assesed and also the concantenated pwm signal of PWM23 is also intialised to be constant 3750Hz with 50%duty cycle, which will serve as a reference. This since both pwm signal will pass through an and gate output of the gate drive the speaker. The reason behind this is when its detected that a surrounding is closer than 0.3m from the lidar, the duty cycle of PWM01 will be made 0% of the period meaning a constant low is given when compared to the PWM23, meaning speaker output is turned off. However other than that case within this system it is used to generate the warning tone when the system is in close proximity to an obstacle.
**The physical output pins of PH3 and PH1 need to be connected to the inputs of an AND gate, and the output of the AND gate to the speaker input pin.** 

The Lidar is initialized using **Init_speaker_PP3**.
The speaker pitch is controlled by manually adjusting the duty cycle and period register of concatenated PWM channel 23.
The speaker pulse rate and length of pulse is controlled by manually adjusting the duty cycle and period register of concatenated PWM channel 01.

```c
void Init_speaker_PP3(void); //Initializes speaker, call on activation
```

##### -servo_controller.c

The servo controller module consists of two segements or functions. One segement being servo_controller(), which involves the intialisation of the two pwm signals used and the other being update_servo(), is responsible for controlling the sweeping motion left and right, also up and down. In the the intialisation function registers are altered to form two PWM signals, which are two concantenated singals of PWM6 and 7, also the concantenated signal of PWM4 and 5. Both PWM's will be made to be left aligned. Where the two clocks they run off will be scaled down by a factor of 128. Also in this function bounds are set up for both the veterical and horizontal movement in terms of duty cycle, along with the bounds the value in which the duty cycle will increment or decrement for the two respective concatenated signals will be intialised. The other function or sgement which is responsible for controlling the horizontal and vertical sweep and is called from main. Inparticular the code  will first check if the vertical upper bound for duty cyle has been surpassed or equated to, inturn instead of incrementing the duty cycle the code will then decrement.This is the opposite when the code checks to see vertrical lower bound has been reached or surpassed. Once that has happened the code will perform the same procedure for the leftmost and right most bounds. Then the vertical sweeping pwm signal of pwm45 is incremented or decremented where the move will be allowed a 200ms delay to move the servo. Then the horizontal sweeping servo's duty cycle of pwm67 is incremented or decremented . This move is then afforded a 300ms delay before control is returned to main.

The two functions are corresponding to two respective segments spoken above.
```c
void servo_controller(void); //intialising the servo signals.

void update_servo(void); //updating the horizontal and vertical sweeping motion of the servos.

```

##### -timers.c

The Timer module contains functions that perform software interrupts by looping mathematical operations.
Within this system it is used to provide a delay for servo movements and to limit the refresh rate of the main loop/LCD.

The four function each provide different lengths of delay.
```c
void delayby1ms(void); //1ms delay

void delayby10ms(void); //10ms delay

void delayby100ms(void); //100ms delay

void delayby1s(void); //1s delay
```

##### -Button.c

DIP switch 8 (PH0) is used to switch the device in and out of reverse mode. Initially,when the system starts, 
the status of the register is first determined. If the value is high, the device will immediately start in 
reverse mode. If the register value is low, then the device will remain dormant. When the switch is pulled high, 
an interrupt will trigger and the device enters reverse mode. When the switch is pulled low, another interrupt 
will trigger and the device exits reverse mode. 

The following functions are in the corresponding header file. 

```c
void init_button(void); //Initialises button registers

void enter_reverse_mode(void); // Switches system to enter reverse mode

void exit_reverse_mode(void); // Switches system to exit reverse mode

```

## Testing
1) Button test:<br/>
Test: Start the device with button pulled low<br/>
Expected Result: The device should be dormant<br/>

Test: Start the device with the button pulled high<br/>
Expected Result: The device should start in reverse mode<br/>

2) LIDAR and LCD test:<br/>
Test: Place an object in front of the LIDAR and vary the distance from the LIDAR<br/>
Expected Result: The distance of the object from the LIDAR should be displayed on the LCD and should update in real-time<br/>

3) Speaker test:<br/>
Test: Place an object directly in front of the LIDAR and slowly move it further away from the LIDAR <br/>
Expected Result: There should be one continuous beep as the object is right in front of the LIDAR and the beeping should 
become less frequent the further away the object is from the sensor.

4) Servo test: <br/>
Test: The servo was tested by dialing in to the pwm registers what 0 degree positions was interms of duty cycle in relation to a 20ms period and the servo was then tested by dialing into the registers the required duty cycle for sweeping to 180 degrees.
Expected: It would first got to a position marking 0 degrees and then would got to a position marking 180 degrees.


