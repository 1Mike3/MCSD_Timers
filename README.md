# Assignment 2 Timers 

* Class: 		Microcontroller Software Design MCSD-EN-1
* Name: 		GPIO Task
* Creator: 		Michal Kuc
* email:		michalkuc55@gmail.com
* Created:		14.10.2023

# Known Bugs:
* Button Press function is a bit buggy, don't konw why, maybe you know what's going on
* The non-Blocking funciton visuals only work correcty for the first button press because 
the blinky function stays on for a while afterwards(the function itself is fine)

# Function Description
	The Code Runs in a While true loop in main.
	Ther User can switch between the blocking and nonblocking version by pushing the Button.
	Blocking funtion active on Startup.
	Nonblocking funciton activated on Buttion Press.
	To visually distiguish the funcitons:
	Blocking funciton uses the green LED.
	Non-Blocking fucntion uses the blue LED.
	For a better visualization during the idle time the led flashes white to show that code is executed
	during the timer wait time in the non-blocking funciton.(see bugs)
	The delaytimes can be adjusted by defines in the main loop.
	
	

# General Information:
* Documentation of used functions is in .h and not .c file
* Prints to Console implemented very crudely, but not part of assignment
* Added Debug Statement and Toggle Red LED in Error handeler to detect if the System goes belly up
*

# Concerning the Blocking functions
* I tried and failed repeatedly to use the HAL SLEEP Command, i have no clue why i can't make the commented out code work,
i made it work anyway by polling the SR register.

