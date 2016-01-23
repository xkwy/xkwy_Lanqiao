
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
    
    /*  */
    ADC1->CR1 = ((3-1) << 13)       /* Discontinuous channel count: 3 */
              | ADC_CR1_JDISCEN;    /* Discontinuous mode on injected channels enabled */
    
    ADC1->CR2 = ADC_CR2_TSVREFE     /* Temperature sensor and VREFINT channel enabled */
              | ADC_CR2_JEXTTRIG    /* Conversion on external event enabled */
              | ADC_CR2_JEXTSEL     /* External event select: JSWSTART */
              | ADC_CR2_ADON;       /* Enable ADC and to start conversion */
    
    /* Reset calibration */
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL);
    
    /* A/D Calibration */
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);
    
    /* ADC sample time register */
    ADC1->SMPR1 = ADC_SMPR1_SMP12
                | ADC_SMPR1_SMP16
                | ADC_SMPR1_SMP17;
    /* ADC injected sequence register */
    ADC1->JSQR = ((3-1) << 20)      /* Injected sequence length: 3 conversions */
               | (8 << 5)           /* ADC1_IN8: PB0 */
               | (16 << 10)         /* ADC1_IN16: Temperature sensor */
               | (17 << 15);        /* ADC1_IN17: VREFINT */
}

extern void ADC_GetVal(uint32_t *dt)    /* max is 65535 */
{
    uint32_t i;
    
    dt[2] = dt[1] = dt[0] = 0;
    
    for (i = 0; i < 16; i++)
    {
        ADC1->CR2 |= ADC_CR2_JSWSTART;
        while (0 == (ADC1->SR&ADC_SR_JEOC));
        
        dt[0] += ADC1->JDR1;
        dt[1] += ADC1->JDR2;
        dt[2] += ADC1->JDR3;
    }
}

extern uint32_t ADC_GetRes(void)        /* return 384 is 38.4% */
{
    uint32_t val[3];
    
    ADC_GetVal(val);
    
    return val[0]*1000ul/65520ul;
}

extern uint32_t ADC_GetTemp(void)       /* return 26120 is 26.120 *C */
{
    int32_t tmp;
    uint32_t val[3];
    
    ADC_GetVal(val);
    tmp = 1200ul*val[1]/val[2];
    return (1430 - tmp)*10000l/43l + 25000l;
}

/* End Line */
