
#include "main.h"
#include "debug_functions.h"
#include "timer_functions.h"

//Timer Handles
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
// UART handle
extern UART_HandleTypeDef huart2;

//Timer INIT is done in main.c

void _tim_timeout_blocking(uint32_t time){

	 printDebug(&huart2 ,"  Entered blocking function \n\n \r");
	 //Activate The Timer
	 HAL_TIM_Base_Init(&htim6);
	 TIM6->ARR = time;
	  HAL_TIM_Base_Start_IT(&htim6);

	  // Old school way, worked but trying correct sleep mode

	  //Put the System in Idle while the Timer Runs
	  int timerStatus = 1; // 0 == TimerIsCounting, 1 == Timer has counted up to it's Value
	  while(timerStatus){
		  timerStatus = (TIM6->SR != 0x1); //Checking for the status of the SR Register
		//  printDebug(&huart2 ,"  Timer is Waiting  \n\n \r");
		//  HAL_Delay(1000);
	  }


	  // I have tried it Time and Time again with the SLLEPMode function but it just doesn't work no matter what

	  /*
	  // According to Documentation Systicks have to be disabled ... so lets do this
	  HAL_SuspendTick();
	  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	  HAL_ResumeTick();
*/
}


void _tim_timeout_nonblocking_with_callback(uint16_t time,void (*callbacFunction)(void) ){

	 printDebug(&huart2 ,"  Entered NON blocking function \n\n \r");
	 //Activate The Timer
	 HAL_TIM_Base_Init(&htim7);
	 TIM7->ARR = time;
	  HAL_TIM_Base_Start_IT(&htim7);

	  // Old school way, worked but trying correct sleep mode

	  //Put the System in Idle while the Timer Runs
	  int timerStatus = 1; // 0 == TimerIsCounting, 1 == Timer has counted up to it's Value
	  while(timerStatus){
		  timerStatus = (TIM7->SR != 0x1); //Checking for the status of the SR Register
		//  printDebug(&huart2 ,"  Timer is Waiting  \n\n \r");
		//  HAL_Delay(1000);
	  }


	callbacFunction();
}

void customCallbackFunction(void){
	printDebug(&huart2 ,"  enteredCallbackFucntion \n\n \r");
}



// Interrupt Routine
//TIM 6 Interrupt
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim6){
		// Print Debug Message
		 printDebug(&huart2 ,"  Entered Interrupt  \n\n \r");
		  // Toggle the Green LED Pin
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
		  //TIM6->ARR &= 0x0;
		  HAL_TIM_Base_Stop_IT(&htim6);
		  	  printDebug(&huart2 ,"  Timer Finished Waiting  \n\n \r");
	} else if (htim == &htim7){
		// Print Debug Message
			 printDebug(&huart2 ,"  Entered Interrupt  \n\n \r");
			  // Toggle the Green LED Pin
			  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
			  //TIM6->ARR &= 0x0;
			  HAL_TIM_Base_Stop_IT(&htim7);
			  	  printDebug(&huart2 ,"  Timer Finished Waiting  \n\n \r");
	}

}



