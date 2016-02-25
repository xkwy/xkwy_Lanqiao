
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      at24c02.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-2-2
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# include "stdint.h"
# include "stm32f10x.h"                  // Device header
# include "at24c02.h"
# include "SoftwareDelay.h"

# define SDA_INPUT     BITBAND_REG(GPIOB->IDR, 7)

# define SCL_OUTPUT    BITBAND_REG(GPIOB->ODR, 6)
# define SDA_OUTPUT    BITBAND_REG(GPIOB->ODR, 7)

static void I2C_Start(void)
{
    SDA_OUTPUT = 1;
    SCL_OUTPUT = 1;
    delay_us(3);
    
    SDA_OUTPUT = 0;
    delay_us(1);                /* Thd1 > 0.6us */
    SCL_OUTPUT = 0;
}

static uint32_t I2C_Write(uint8_t dt)
{
    uint32_t i;
    uint32_t re_val;
    const uint8_t TB_MASK[] = {(1<<7),(1<<6),(1<<5),(1<<4),(1<<3),(1<<2),(1<<1),(1<<0)};
    
    for (i = 0; i < 8; i++)
    {
        SDA_OUTPUT = (dt&TB_MASK[i]) ? 1 : 0;
        
        delay_us(2);            /* Tlo > 1.3us, Tst2 > 0.1us */
        SCL_OUTPUT = 1;
        delay_us(1);            /* Thi > 0.6us */
        SCL_OUTPUT = 0;
    }
    
    delay_us(1);                /* Thd2 > 0 */
    SDA_OUTPUT = 1;          /* Ensure release signal */
    
    delay_us(2);                /* Tlo > 1.3us, Tst2 > 0.1us */
    SCL_OUTPUT = 1;
    delay_us(1);                /* Thi > 0.6us */
    re_val = SDA_INPUT;
    SCL_OUTPUT = 0;
    
    return re_val;
}

static uint8_t I2C_Read(uint32_t respond)
{
    uint32_t i;
    uint8_t re_val;
    
    SDA_OUTPUT = 1;          /* Ensure release signal */
    
    for (i = 0; i < 8; i++)
    {
        delay_us(2);            /* Tlo > 1.3us, Tst2 > 0.1us */
        SCL_OUTPUT = 1;
        delay_us(1);            /* Thi > 0.6us */
        re_val <<= 1;
        re_val += SDA_INPUT;
        SCL_OUTPUT = 0;
    }
    
    delay_us(1);                /* Thd2 > 0 */
    SDA_OUTPUT = respond ? 1 : 0;
    
    delay_us(2);                /* Tlo > 1.3us, Tst2 > 0.1us */
    SCL_OUTPUT = 1;
    delay_us(1);                /* Thi > 0.6us */
    SCL_OUTPUT = 0;
    
    return re_val;
}

static void I2C_Stop(void)
{
    SDA_OUTPUT = 0;
    SCL_OUTPUT = 0;
    delay_us(3);
    
    SCL_OUTPUT = 1;
    delay_us(1);                /* Tst3 > 0.6us */
    SDA_OUTPUT = 1;
}

/******************************************************/

extern void AT24C02_init(void)
{
    /* SCL:PB6, SDA:PB7 */
    
    /* Enable GPIOB Clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    
    /* PB6, PB7: Output, 50MHz, Open-drain */
    GPIOB->CRL &= ~((GPIO_CRL_MODE6|GPIO_CRL_CNF6)
                  | (GPIO_CRL_MODE7|GPIO_CRL_CNF7));
    GPIOB->CRL |= ((GPIO_CRL_MODE6|GPIO_CRL_CNF6_0)
                 | (GPIO_CRL_MODE7|GPIO_CRL_CNF7_0));
}

extern void AT24C02_Write(void *val, uint8_t n, uint8_t Addr)
{
    uint8_t *p = val;
    
    I2C_Start();
    I2C_Write(0xA0);
    I2C_Write(Addr);
    while (n --> 0) I2C_Write(*p++);
    
    I2C_Stop();
}

extern void AT24C02_Read(void *val, uint8_t n, uint8_t Addr)
{
    uint8_t *p = val;
    
    I2C_Start();
    I2C_Write(0xA0);
    I2C_Write(Addr);
    
    I2C_Start();
    I2C_Write(0xA1);
    while (n --> 1) *p++ = I2C_Read(0);
    *p = I2C_Read(1);
    
    I2C_Stop();
}

/* End Line */
