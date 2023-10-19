/*
 * debug_function.c
 *
 *  Created on: Oct 14, 2023
 *      Author: Michi
 */

#include "stm32l4xx_hal.h"

#include "stdio.h"
#include "main.h"
#include "string.h"


// Print a message using the UART Interface
void printDebug(UART_HandleTypeDef * huart, char * text){
       HAL_UART_Transmit(huart, (uint8_t *) text, strlen(text),100);
	        HAL_UART_AbortTransmit(huart);
}

