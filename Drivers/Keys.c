
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      keys.c
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
# include "keys.h"

extern void KEY_EventUp(uint32_t index);
extern void KEY_EventDown(uint32_t index);

static volatile struct
{
    void (*volatile f_up)(uint32_t);
    void (*volatile f_dn)(uint32_t);
    
    uint32_t volatile status[4];
    uint32_t volatile history[4];
    volatile uint32_t *volatile pin_addr[4];
} KEY_Mgr_t;

__attribute__((weak)) void KEY_EventUp(uint32_t index)
{
    __nop(); __nop(); __nop(); __nop();
}

__attribute__((weak)) void KEY_EventDown(uint32_t index)
{
    __nop(); __nop(); __nop(); __nop();
}

extern void KEY_Scan(void)
{
    uint32_t i;
    
    for (i = 0; i < 4; i++) KEY_Mgr_t.history[i] <<= 1;
    for (i = 0; i < 4; i++) KEY_Mgr_t.history[i] |= *KEY_Mgr_t.pin_addr[i];
    
    for (i = 0; i < 4; i++)
    {
        if (0xFFFFFFFF == KEY_Mgr_t.history[i])
        {
            if (1 == KEY_Mgr_t.status[i]) continue;
            KEY_Mgr_t.status[i] = 1;
            KEY_Mgr_t.f_up(i);
            continue;
        }
        
        if (0x00000000 == KEY_Mgr_t.history[i])
        {
            if (0 == KEY_Mgr_t.status[i]) continue;
            KEY_Mgr_t.status[i] = 0;
            KEY_Mgr_t.f_dn(i);
            continue;
        }
    }
}

extern void KEY_init(void)
{
    /* PA0,PA8,PB1,PB2 */
    
    /* Enable GPIOA Clock, GPIOB Clock */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPBEN);
    
    /* PA0: Input with pull-up */
    GPIOA->CRL &= ~(GPIO_CRL_MODE0|GPIO_CRL_CNF0);
    GPIOA->CRL |= GPIO_CRL_CNF0_1;
    GPIOA->ODR |= (1<<0);               /* pull-up */
    
    /* PA8: Input with pull-up */
    GPIOA->CRH &= ~(GPIO_CRH_MODE8|GPIO_CRH_CNF8);
    GPIOA->CRH |= GPIO_CRH_CNF8_1;
    GPIOA->ODR |= (1<<8);               /* pull-up */
    
    /* PB1,PB2: Input with pull-up */
    GPIOB->CRL &= ~((GPIO_CRL_MODE1|GPIO_CRL_CNF1)
                  | (GPIO_CRL_MODE2|GPIO_CRL_CNF2));
    GPIOB->CRL |= (GPIO_CRL_CNF1_1|GPIO_CRL_CNF2_1);
    GPIOB->ODR |= ((1<<1)|(1<<2));      /* pull-up */
    
    
    KEY_Mgr_t.status[0] = 1;
    KEY_Mgr_t.status[1] = 1;
    KEY_Mgr_t.status[2] = 1;
    KEY_Mgr_t.status[3] = 1;
    KEY_Mgr_t.history[0] = 0xFFFFFFFF;
    KEY_Mgr_t.history[1] = 0xFFFFFFFF;
    KEY_Mgr_t.history[2] = 0xFFFFFFFF;
    KEY_Mgr_t.history[3] = 0xFFFFFFFF;
    KEY_Mgr_t.pin_addr[0] = pBITBAND_REG(GPIOA->IDR,0);
    KEY_Mgr_t.pin_addr[1] = pBITBAND_REG(GPIOA->IDR,8);
    KEY_Mgr_t.pin_addr[2] = pBITBAND_REG(GPIOB->IDR,1);
    KEY_Mgr_t.pin_addr[3] = pBITBAND_REG(GPIOB->IDR,2);
    
    KEY_Mgr_t.f_up = KEY_EventUp;
    KEY_Mgr_t.f_dn = KEY_EventDown;
}

extern uint32_t KEY_GetStatus(uint32_t index)
{
    return KEY_Mgr_t.status[index];
}

extern void Start_Check(void)
{
    /* Enable Port A Clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    
    /* PA0: Input with pull-up */
    GPIOA->CRL &= ~(GPIO_CRL_MODE0|GPIO_CRL_CNF0);
    GPIOA->CRL |= GPIO_CRL_CNF0_1;
    GPIOA->ODR |= (1<<0);               /* pull-up */
    
    while (0 == BITBAND_REG(GPIOA->IDR,0));
}

/* End Line */
