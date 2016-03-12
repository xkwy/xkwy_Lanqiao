
#include "stm32f10x.h"                  // Device header


void tim_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    
    GPIOA->CRL ^= 0xFF000000;
    
    TIM3->PSC = 1;
    
    TIM3->CCMR1 = (6<<12);
    
    TIM3->CCER = 0x10;
    
    TIM3->CR1 = 1;
}

void tim_set(u32 f_khz)
{
    TIM3->ARR = ((36000+f_khz/2)/f_khz) - 1;
    TIM3->CCR2 = TIM3->ARR >> 1;
}



