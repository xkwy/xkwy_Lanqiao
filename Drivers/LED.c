
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      led.c
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
# include "led.h"

static uint32_t led_status;

extern void LED_init(void)
{
    /* Enable GPIOC Clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    
    GPIOC->CRH = GPIO_CRH_MODE;
    
    /* Enable GPIOD Clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
    
    GPIOD->CRL &= ~GPIO_CRL_CNF2;
    GPIOD->CRL |= GPIO_CRL_MODE2;
    
    
    LED_OFF(LED_ALL);
}

static void LED_Update(void)
{
    BITBAND_REG(GPIOD->ODR, 2) = 0;
    
    GPIOC->ODR = ((led_status<<8)&0x0000FF00)|(GPIOC->ODR&(~0x0000FF00));
    
    BITBAND_REG(GPIOD->ODR, 2) = 1;
}

extern void LED_ON(LED_t led)
{
    led_status &= ~led;
    
    LED_Update();
}

extern void LED_OFF(LED_t led)
{
    led_status |= led;
    
    LED_Update();
}

extern void LED_TOG(LED_t led)
{
    led_status ^= led;
    
    LED_Update();
}


/* End Line */
