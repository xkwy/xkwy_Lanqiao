

#include "stm32f10x.h"                  // Device header

u32 tim1_val = 0;

u32 fal = 0;
u32 re = 0;
u32 wid = 0;
u32 pp = 0;
void TIM1_UP_IRQHandler(void)
{
    TIM1->SR = ~1;
    tim1_val += 0x10000;
}

void TIM1_CC_IRQHandler(void)
{
    u32 sr = TIM1->SR;
    u32 tmp;
    if (sr & 2)
    {
        TIM1->SR = ~2;
        tmp = tim1_val + TIM1->CCR1;
        wid = tmp - re;
        re = tmp;
    }
    else if (sr & 4)
    {
        TIM1->SR = ~4;
        
        fal = tim1_val + TIM1->CCR2;
        
        pp = fal - re;
    }
}

void cap_init(void)
{
    /* TIM1_CH1: PA8 */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    
    TIM1->CCMR1 = 0x201;
    TIM1->CCER = 0x31;
    
    TIM1->DIER = 0x7;
    
    TIM1->CR1 = 1;
    
    NVIC_EnableIRQ(TIM1_UP_IRQn);
    NVIC_EnableIRQ(TIM1_CC_IRQn);
}



