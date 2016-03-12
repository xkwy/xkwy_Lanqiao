
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      pwm.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-2-4
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# include "stdint.h"
# include "stm32f10x.h"                  // Device header
# include "pwm.h"

extern void PWM_init(void)
{
    /* Enable GPIOA Clock, GPIOB Clock */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPBEN);
    
    /* PA9: TIM1_CH2, PB14: TIM1_CH2N */
    GPIOA->CRH &= ~(GPIO_CRH_MODE9|GPIO_CRH_CNF9);
    GPIOA->CRH |= (GPIO_CRH_MODE9|GPIO_CRH_CNF9_1);
    GPIOB->CRH &= ~(GPIO_CRH_MODE14|GPIO_CRH_CNF14);
    GPIOB->CRH |= (GPIO_CRH_MODE14|GPIO_CRH_CNF14_1);
    
    /* Enable TIM1 Clock */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    
    /* Reset TIM1 */
    RCC->APB2RSTR |= RCC_APB2RSTR_TIM1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM1RST;
    
    /* CH2: PWM mode 1 */
    TIM1->CCMR1 = (TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1);
    
    /* CH2 and CH2N output enable */
    TIM1->CCER = (TIM_CCER_CC2E|TIM_CCER_CC2NE);
    
    /* TIM1_CNT Clock: 36MHz */
    TIM1->PSC = 1;
    
    /* TIM1 Counter Enable */
    TIM1->CR1 = TIM_CR1_CEN;
}

extern void PWM_Set(uint32_t freq, uint32_t wid)
{
    /* Main output enable */
    TIM1->BDTR = TIM_BDTR_MOE;
    
    TIM1->ARR = 36000/freq - 1;
    TIM1->CCR2 = 360/freq*wid;
}

extern void PWM_Disable(void)
{
    TIM1->BDTR = 0;
}

/* End Line */
