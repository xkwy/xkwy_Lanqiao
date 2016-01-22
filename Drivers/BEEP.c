
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      beep.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-22
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# include "stdint.h"
# include "stm32f10x.h"                  // Device header
# include "beep.h"

static volatile uint32_t beep_remain_ms;

extern void BEEP_Scan(void)
{
    if (beep_remain_ms)
    {
        beep_remain_ms--;
    }
    else
    {
        /* Disable Output */
        BITBAND_REG(GPIOB->ODR, 4) = 1;
    }
}

extern void BEEP_init(void)
{
    /* Enable AFIO Clock */
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    
    /* Full SWJ (JTAG-DP + SW-DP) but without NJTRST */
    AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_NOJNTRST;
    
    /* Enable GPIOB Clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    
    /* General purpose output Open-drain */
    GPIOB->CRL &= ~GPIO_CRL_CNF4_1;
    GPIOB->CRL |= (GPIO_CRL_MODE4|GPIO_CRL_CNF4_0);
    
    BEEP_Set(0);
}

extern void BEEP_Set(uint32_t time_ms)
{
    BITBAND_REG(GPIOB->ODR, 4) = time_ms ? 0 : 1;
    
    beep_remain_ms = time_ms;
}

extern uint32_t BEEP_GetRemain(void)
{
    return beep_remain_ms;
}

extern void BEEP_Stop(void)
{
    beep_remain_ms = 0;
    BITBAND_REG(GPIOB->ODR, 4) = 1;
}




/* End Line */
