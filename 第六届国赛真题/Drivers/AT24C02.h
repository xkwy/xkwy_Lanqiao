
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      at24c02.h
 * @author    xkwy
 * @version   V1.00
 * @date      2016-2-2
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __AT24C02_H_
# define __AT24C02_H_

# include "stdint.h"
/**
 * @brief Macro to access a single bit of a peripheral register (bit band region
 *        0x40000000 to 0x400FFFFF) using the bit-band alias region access.
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return Value of the targeted bit in the bit band region.
 */
#define BITBAND_REG(Reg,Bit) (*((uint32_t volatile*)(0x42000000u + (32u*((uint32_t)&(Reg) - (uint32_t)0x40000000u)) + (4u*((uint32_t)(Bit))))))

static void I2C_Start(void);
static uint32_t I2C_Write(uint8_t by);
static uint8_t I2C_Read(uint32_t respond);
static void I2C_Stop(void);

extern void AT24C02_init(void);
extern void AT24C02_Write(void *val, uint8_t n, uint8_t Addr);
extern void AT24C02_Read(void *val, uint8_t n, uint8_t Addr);

# endif
