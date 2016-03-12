

#include "stm32f10x.h"                  // Device header


void rtc_init(u8 h, u8 m, u8 s)
{
    u32 val;
    
    RCC->CSR = 1;
    while (2&~RCC->CSR);
    
    RCC->APB1ENR |= (RCC_APB1ENR_PWREN|RCC_APB1ENR_BKPEN);
    
    PWR->CR |= PWR_CR_DBP;
    
    RCC->BDCR = 0x8200;
    
    RTC->CRL = 0x10;
    
    RTC->PRLH = 0;
    RTC->PRLL = 40000 - 1;
    val = h*3600 + m*60 + s;
    RTC->CNTH = val >> 16;
    RTC->CNTL = val;
    
    RTC->CRL = 0;
}




