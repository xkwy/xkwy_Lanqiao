
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      rtc.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-2-3
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# include "stdint.h"
# include "stm32f10x.h"                  // Device header
# include "rtc.h"

extern void RTC_Update(uint32_t h, uint32_t m, uint32_t s);

__attribute__((weak)) void RTC_Update(uint32_t h, uint32_t m, uint32_t s)
{
    __nop(); __nop(); __nop(); __nop();
}

void RTC_IRQHandler(void)
{
    uint32_t rtc_val;
    uint32_t h, m, s;
    
    if (RTC->CRL & RTC_CRL_SECF)
    {
        RTC->CRL &= ~RTC_CRL_SECF;
        
        rtc_val = RTC->CNTL + 1;
        rtc_val |= RTC->CNTH << 16;
        
        if (rtc_val >= 24ul*60ul*60ul)
        {
            rtc_val = 0;
            
            RTC->CRL |= RTC_CRL_CNF;    /* Enter Configuration mode */
            RTC->CNTH = 0;
            RTC->CNTL = 0;
            RTC->CRL &= ~RTC_CRL_CNF;   /* Exit Configuration mode */
        }
        
        h = rtc_val / 3600;
        rtc_val %= 3600;
        m = rtc_val / 60;
        s = rtc_val % 60;
        
        RTC_Update(h, m, s);
    }
}

extern void RTC_init(uint32_t h, uint32_t m, uint32_t s)
{
    uint32_t pre_val = h*60ul*60ul + m*60ul + s;
    
    /* Enable access to the Backup registers and the RTC */
    RCC->APB1ENR |= (RCC_APB1ENR_PWREN|RCC_APB1ENR_BKPEN);
    PWR->CR |= PWR_CR_DBP;
    
    /* Enable 40kHz LSI */
    RCC->CSR |= RCC_CSR_LSION;
    while (!(RCC->CSR&RCC_CSR_LSIRDY));
    
    /* Enable RTC, Select LSI as Clock */
    RCC->BDCR = (RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL_LSI);
    
    /* Enter Configuration mode */
    RTC->CRL |= RTC_CRL_CNF;
    
    /* Set prescaler load value */
    RTC->PRLH = (40000-1) >> 16;
    RTC->PRLL = (40000-1) & 0xFFFF;
    
    /* Set CNT */
    RTC->CNTH = pre_val >> 16;
    RTC->CNTL = pre_val & 0xFFFF;
    
    /* Enable second interrupt */
    RTC->CRH = RTC_CRH_SECIE;
    
    /* Exit Configuration mode */
    RTC->CRL &= ~RTC_CRL_CNF;
    
    NVIC_EnableIRQ(RTC_IRQn);
}

/* End Line */
