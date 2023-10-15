# Assignment 2 Timers 

* Class: 		Microcontroller Software Design MCSD-EN-1
* Name: 		GPIO Task
* Creator: 		Michal Kuc
* email:		michalkuc55@gmail.com
* Created:		14.10.2023

# Known Bugs:

* Green LED flashes two times on Startup and i don#t know why 
* According to the Serial Debug Prints the Interrupt gets triggered right after calling
the blocking function but it seems to work anyway...

# General Information:

* Documentation of used functions is in .h and not .c file
* Prints to Console implemented very crudely, but not part of assignment
* Added Debug Statement and Toggle Red LED in Error handeler to detect if the System goes belly up
*

# Concerning the Blocking functions
* It seems Like the function Enters the Timmer Interrupt on Startup but the function seems to be working as intended?
* I tried and failed repeatedly to use the HAL SLEEP Command, i have no clue why i can't make the commented out code work
* Other than that i made it work but something is weird