
#include "main.h"
#include "debug_functions.h"
#include "timer_functions.h"
#include "stm32l4xx_hal_tim.h"

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
		  ;
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
/*
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
*/
				HAL_TIM_Base_Stop_IT(&htim6);
				HAL_GPIO_WritePin(GPIOA, LED_BLUE_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_SET);

		 printDebug(&huart2 ,"  Entered NON blocking function \n\n \r");
	 //Activate The Timer
	 HAL_TIM_Base_Init(&htim7);
	 TIM7->ARR = time;
	  HAL_TIM_Base_Start_IT(&htim7);


// safe the callback function to use it later in the interrupt
safeCallbackFunciton(SAFECALLBACKFUCNTIONMODE_WRITE, callbacFunction);


}




void customCallbackFunction(void){
	printDebug(&huart2 ,"  enteredCallbackFucntion \n\n \r");
	HAL_GPIO_TogglePin(GPIOA, LED_BLUE_Pin);
	for(int i = 0; i < 10000000; i++){
		;
	}
}



void * safeCallbackFunciton(int mode,Callbackfuntion fptr){
	static Callbackfuntion safedfptr = NULL;
	if(mode == SAFECALLBACKFUCNTIONMODE_WRITE){
		safedfptr = fptr;
	}
	if(mode == SAFECALLBACKFUCNTIONMODE_READ){
		return safedfptr;
	}
return NULL;
}

void helperSetAllLedLow(void){
	  HAL_GPIO_WritePin(GPIOA, LED_BLUE_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_SET);
}

//Helper fucntion Blink LED
void helperBlink(int count, int frequency){
	  for(int i = 0; i < count; i++){
		  HAL_Delay(frequency);
		  HAL_GPIO_WritePin(GPIOA, LED_BLUE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_RESET);
		  HAL_Delay(frequency);
		 helperSetAllLedLow();
		  HAL_Delay(frequency);
		  }
}


// Interrupt Routine timers
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
		helperSetAllLedLow();
		Callbackfuntion f = safeCallbackFunciton(SAFECALLBACKFUCNTIONMODE_READ, NULL);
			 if(f != NULL){

			// Print Debug Message
				 printDebug(&huart2 ,"  Entered Interrupt  \n\n \r");
				  // Toggle the Green LED Pin
//				  HAL_GPIO_TogglePin(GPIOA, LED_BLUE_Pin);
				  //TIM6->ARR &= 0x0;
				  HAL_TIM_Base_Stop_IT(&htim7);
					  f();
					  printDebug(&huart2 ,"  Timer Finished Waiting  \n\n \r");
			 }
		 }

}



