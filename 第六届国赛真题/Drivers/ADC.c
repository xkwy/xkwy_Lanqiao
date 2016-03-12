
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      adc.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-23
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# include "stdint.h"
# include "stm32f10x.h"                  // Device header
# include "adc.h"

extern void ADC_init(void)
{
    /* Enable GPIOB Clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    
    /* PB0: Input mode, Analog mode */
    GPIOB->CRL &= ~(GPIO_CRL_CNF0|GPIO_CRL_MODE0);
    
    /* ADC prescaler */
    RCC->CFGR &= ~RCC_CFGR_ADCPRE;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
    
    /* Enable ADC1 clock */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    
    /* Reset ADC1 */
    RCC->APB2RSTR |= RCC_APB2RSTR_ADC1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_ADC1RST;
    
    ADC1->CR2 = ADC_CR2_JEXTTRIG    /* Conversion on external event enabled */
              | ADC_CR2_JEXTSEL     /* External event select: JSWSTART */
              | ADC_CR2_ADON;       /* Enable ADC and to start conversion */
    
    /* ADC injected sequence register */
    ADC1->JSQR = ((3-1) << 20)      /* Injected sequence length: 3 conversions */
               | (8 << 5);          /* ADC1_IN8: PB0 */
}

extern double ADC_GetVolt(void)        /* max 3.3V */
{
    uint32_t val;
    ADC1->CR2 |= ADC_CR2_JSWSTART;
    while (!(ADC1->SR&ADC_SR_JEOC));
    
    val = ADC1->JDR1;
    if (val > ADC_MAX) val = ADC_MAX;
    return val * 3.3 / ADC_MAX;
}

/* End Line */
