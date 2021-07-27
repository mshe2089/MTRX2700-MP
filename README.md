# MTRX2700-major
Authors - Jan Lum - ???????????????

Daniel Shen - Responsible for ??????????

Travis Giannarakis - Responsible for ????????????

## Usage:

~~??????????~~

## Module overview:

##### -LCD.c

The LCD module handles all processes relating to the HD44780U LCD.
Within this system the LCD is programmed to display lidar distance information and a warning message accordingly.

The LCD is initialized using **openLCD**.
Null terminated strings can sent to the LCD and displayed with **puts2LCD**.
Clearing, cursor movements and other functionalities are performed by sending instruction sets with **cmd2LCD**. Refer to HD44780U datasheet for details.

```c
openLCD(void); //Initializes LCD, call on activation

putsLCD(string S); //Outputs a null-terminated string S to LCD

cmd2LCD(char cmd); //Output instruction set byte cmd to LCD
```

##### -lidar.c

The Lidar module measures PWM pulse width transmitted from the LIDAR-Lite v2. It is connected to PT1 on cont trigger and uses interrupts to track time. 
Within this system it is used to track the proximity of nearby obstacles.

There is no functionality to trigger on PH0; the Lidar unit is presumed to be in continuous trigger mode.
Any accompanying module that uses interrupts must halt the timer or disable PT1 interrupts upon interrupt to prevent distance calculation errors.

The Lidar is initialized using **Init_lidar**.
The last lidar measurement taken, in meters, can be acquired using **GetDist**.

```c
Init_lidar(void); //Initializes Lidar, call on activation

GetDist(void); //Returns last distance measurement in meters (double)
```

##### -speaker.c

The Speaker module initializes two PWM signals used to drive the on board speaker.
Within this system it is used to generate the warning tone when the system is in close proximity to an obstacle.
**The physical output pins of PH3 and PH1 need to be connected to the inputs of an AND gate, and the output of the AND gate to the speaker input pin.** 

The Lidar is initialized using **Init_speaker_PP3**.
The speaker pitch is controlled by manually adjusting the duty cycle and period register of concatenated PWM channel 23.
The speaker pulse rate and length of pulse is controlled by manually adjusting the duty cycle and period register of concatenated PWM channel 01.

```c
Init_speaker_PP3(void); //Initializes speaker, call on activation
```

##### -servo_controller.c

Finish
```c
me
```

##### -timers.c

The Timer module contains functions that perform software interrupts by looping mathematical operations.
Within this system it is used to provide a delay for servo movements and to limit the refresh rate of the main loop/LCD.

The four function each provide different lengths of delay.
```c
delayby1ms(void); //1ms delay

delayby10ms(void); //10ms delay

delayby100ms(void); //100ms delay

delayby1s(void); //1s delay
```

##### -Button.c

Finish
```c
me
```

## Testing
~~??????????~~