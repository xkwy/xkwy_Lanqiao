
#include "stm32f10x.h"                  // Device header

u32 arr;

void tim_init(u32 f_khz)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    
    GPIOA->CRL ^= 0xFF000000;
    
    TIM3->PSC = 1;
    arr = (36000/f_khz) - 1;
    TIM3->ARR = arr;
    
    TIM3->CCMR1 = (6<<12);
    
    TIM3->CCER = 0x10;
    
    TIM3->CR1 = 1;
}

void tim_set(u32 p)
{
    TIM3->CCR2 = arr*p/100;
}



