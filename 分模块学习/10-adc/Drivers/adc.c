

#include "stm32f10x.h"                  // Device header


void adc_init(void)
{
    /* PB0: ADC12_IN8 */
    
    GPIOB->CRL &= ~0xF;
    
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    
    ADC1->CR2 = (0x2F<<17) + 3;
    
    ADC1->SQR3 = 8;
}

u32 adc_get(void)
{
    return ADC1->DR;
}

