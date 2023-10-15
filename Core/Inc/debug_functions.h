/*
 * debug_functions.h
 *
 *  Created on: Oct 14, 2023
 *      Author: Michi
 */

#ifndef INC_DEBUG_FUNCTIONS_H_
#define INC_DEBUG_FUNCTIONS_H_

// Function used for Debugging utilizing the Serial Port
void printDebug(UART_HandleTypeDef * huart, char * text);

#endif /* INC_DEBUG_FUNCTIONS_H_ */
