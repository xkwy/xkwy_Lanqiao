
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      SoftwareDelay.c
 * @author    xkwy
 * @version   V1.00
 * @date      2015-12-19
 ******************************************************
 * @attention
 *
 * Copyright (C) 2015 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# include "stdint.h"
# include "stm32f10x.h"
# include "SoftwareDelay.h"

extern uint32_t SystemCoreClock;

static volatile uint32_t SystemCoreClock_div1K;
static volatile uint32_t SystemCoreClock_div1M;

extern void delay_init(void)
{
	SystemCoreClockUpdate();
    
    SystemCoreClock_div1K = SystemCoreClock / 1000UL;
    SystemCoreClock_div1M = SystemCoreClock / 1000UL / 1000UL;
    
    /* Enable DWT and ITM blocks */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    /* Enable DWT's CYCCNT */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

extern void delay_us(const uint32_t us)
{
    uint32_t dwEnd;
    
    DWT->CYCCNT = 0;
    
    dwEnd = us * SystemCoreClock_div1M;
    
    while (DWT->CYCCNT < dwEnd);
}

extern void delay_ms(const uint32_t ms)
{
    uint32_t dwEnd;
    
    DWT->CYCCNT = 0;
    
    dwEnd = ms * SystemCoreClock_div1K;
    
    while (DWT->CYCCNT < dwEnd);
}

/* End Line */
