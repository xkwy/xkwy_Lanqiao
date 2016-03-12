
#include "stm32f10x.h"                  // Device header


void tim_init(u32 us)
{
    /* PA8:TIM1_CH1, PB13:TIM1_CH1N */
    
    GPIOA->CRH ^= 0xF;
    
    GPIOB->CRH ^= 0x00F00000;
    
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    
    TIM1->PSC = 72 - 1;
    TIM1->ARR = us - 1;
    TIM1->CR1 = 1;
    
    TIM1->CCMR1 = (6<<4);
    TIM1->CCER = 1+4+2;
    TIM1->BDTR = (1<<15)+200;
}

void pwm_set(u32 us)
{
    TIM1->CCR1 = us;
    ;
}
