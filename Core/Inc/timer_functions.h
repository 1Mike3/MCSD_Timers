/*
 * timer_functions.h
 *
 *  Created on: Oct 19, 2023
 *      Author: Michi
 */

#ifndef INC_TIMER_FUNCTIONS_H_
#define INC_TIMER_FUNCTIONS_H_

//implementation of a blocking timer function
// par time: the time before the timer Action happens (system blocked until)
void _tim_timeout_blocking(uint32_t time);

//implementation of a non-blocking timer function
// par time: the time before the timer Action happens (system blocked until)
// par callbackFunction: function which will be executed after the time has elapsed
void _tim_timeout_nonblocking_with_callback(uint16_t time,void (*callbacFunction)(void) );

//Custom Callback Function which will be executed after the preset time from the previous function has elapsed
void customCallbackFunction(void);

// stuff for saving the callback funciton
#define SAFECALLBACKFUCNTIONMODE_WRITE 1
#define SAFECALLBACKFUCNTIONMODE_READ 2
typedef void (*Callbackfuntion)(void);
void* safeCallbackFunciton(int mode, Callbackfuntion fptr);

//Helper fucntion Blink LED
void helperBlink(int count, int frequency);

//Helper function to reset all LEDs
void helperSetAllLedLow(void);

// * The Switching between the functions can be done by toggling the button:
// Button State low (onbord LED low) = blocking function active in while true loop (main)
// Button State high (onbord LED high) = non-blocking function active in while true loop (main)

#endif /* INC_TIMER_FUNCTIONS_H_ */
