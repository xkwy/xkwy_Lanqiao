
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      led.h
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-22
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __LED_H_
# define __LED_H_
/**
 * @brief Macro to access a single bit of a peripheral register (bit band region
 *        0x40000000 to 0x400FFFFF) using the bit-band alias region access.
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return Value of the targeted bit in the bit band region.
 */
#define BITBAND_REG(Reg,Bit) (*((uint32_t volatile*)(0x42000000u + (32u*((uint32_t)&(Reg) - (uint32_t)0x40000000u)) + (4u*((uint32_t)(Bit))))))

typedef enum
{
    LED_0 = (1<<0),
    LED_1 = (1<<1),
    LED_2 = (1<<2),
    LED_3 = (1<<3),
    LED_4 = (1<<4),
    LED_5 = (1<<5),
    LED_6 = (1<<6),
    LED_7 = (1<<7),
    
    LED_NULL = 0,
    
    LED_ALL = 0xFF,
} LED_t, *pLED_t;

# include "stdint.h"

static void LED_Update(void);

extern void LED_init(void);
extern void LED_ON(LED_t led);
extern void LED_OFF(LED_t led);
extern void LED_TOG(LED_t led);



# endif
