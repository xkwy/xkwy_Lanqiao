

#include "stm32f10x.h"                  // Device header


void adc_init(void)
{
    /* PB0: ADC12_IN8 */
    /* Temperature sensor: ADC1_IN16 */
    /* voltage VREFINT: ADC1_IN17 */
    
    GPIOB->CRL &= ~0xF;
    
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8;
    
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    
    ADC1->SMPR1 = ADC_SMPR1_SMP16|ADC_SMPR1_SMP17;
    
    ADC1->CR1 = 5 << 8;
    
    ADC1->CR2 = 0x00A0F003;
    
    ADC1->JSQR = (2<<20) | (17<<15) | (16<<10) | (8<<5);
}

u32 adc_get_r(void)
{
    return ADC1->JDR1;
}

u32 adc_get_t(void)
{
    return ADC1->JDR2;
}

u32 adc_get_v(void)
{
    return ADC1->JDR3;
}
