

#include "stm32f10x.h"                  // Device header

u32 tim1_val = 0;

u32 last = 0;
u32 now = 0;
u32 wid = 0;

void TIM1_UP_IRQHandler(void)
{
    TIM1->SR = ~1;
    tim1_val += 0x10000;
}

void TIM1_CC_IRQHandler(void)
{
    TIM1->SR = ~2;
    now = tim1_val + TIM1->CCR1;
    wid = now - last;
    last = now;
}

void cap_init(void)
{
    /* TIM1_CH1: PA8 */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    
    TIM1->CCMR1 = 1;
    TIM1->CCER = 1;
    
    TIM1->DIER = 3;
    
    TIM1->CR1 = 1;
    
    NVIC_EnableIRQ(TIM1_UP_IRQn);
    NVIC_EnableIRQ(TIM1_CC_IRQn);
}



