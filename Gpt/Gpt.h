#include "Std_Types.h"

#define TIM2_BASE_ADDRESS 0x40000000UL
#define RCC_BASE_ADDRESS  0x40023800UL

#define RCC_APB1ENR_OFFSET 0x40UL
#define TIM_CR1_OFFSET     0x00UL
#define TIM_PSC_OFFSET     0x28UL
#define TIM_ARR_OFFSET     0x2CUL
#define TIM_EGR_OFFSET     0x14UL


#define TIM2_BASE_ADDRESS 0x40000000UL
#define TIM_CNT_OFFSET    0x24UL
#define TIM_SR_OFFSET     0x10UL


void GPT_Init(void) ;
void GPT_StartTimer(uint32 OverFlowTicks);
uint32 GPT_GetElapsedTime(void);
uint32  GPT_CheckTimeIsElapsed(void);
uint32 GPT_GetRemainingTime(void);
void TIM2_IRQHandler(void);




























