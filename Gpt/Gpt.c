#include "stm32f4xx.h"
#include "Rcc.h"
#include  "Gpt.h"
#include <stdint.h>

// Global variables
uint32 gpt_overflowFlag = 0;
uint32 gpt_elapsedTicks = 0;
uint32 gpt_remainingTicks = 0;

// GPT initialization function
void GPT_Init(void) {
    // Enable the clock for the timer peripheral
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// Set prescaler 
    TIM2->PSC =  (16000000 / 10000 )-1;
    TIM2->EGR |= 1<< 0;
}


// GPT start timer function
void GPT_StartTimer(uint32 OverFlowTicks) {

	// Disable the timer
	TIM2->CR1 &= ~TIM_CR1_CEN;
    // Reset timer counter and overflow flag
    TIM2->CNT = 0;
    gpt_overflowFlag = 0;

    // Set the number of overflow ticks
    TIM2->ARR = OverFlowTicks;

    // Set the number of overflow ticks
    gpt_remainingTicks = OverFlowTicks;

    // Clear the timer overflow flag
    TIM2->SR &= ~TIM_SR_UIF;

    // Enable the timer
    TIM2->CR1 |= TIM_CR1_CEN;


}


uint32 GPT_CheckTimeIsElapsed(void) {
	int flag;
    if (TIM2->SR &= TIM_SR_UIF) {

    	flag =1;
    }else{
    	flag= 0;
    }
    return flag;
}



uint32 GPT_GetElapsedTime(void) {
	int flag;
	if (TIM2->SR &= TIM_SR_UIF) {
	        gpt_elapsedTicks = 0;
	        gpt_remainingTicks = 0;
	        flag = 0xFFFF;
	    }else{
	    	gpt_elapsedTicks = TIM2->CNT;
	    	flag = gpt_elapsedTicks;
	    }

	return flag;
}



uint32 GPT_GetRemainingTime(void) {

	int flag;

	if (TIM2->SR &= TIM_SR_UIF) {

		 flag= 0;
		    }else{
		    	uint32 remainingTicks = gpt_remainingTicks - TIM2->CNT ;

		    	flag= remainingTicks;
		    }

	return flag;

}


