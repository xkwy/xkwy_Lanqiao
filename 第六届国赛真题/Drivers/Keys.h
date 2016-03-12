
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      keys.h
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-22
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __KEYS_H_
# define __KEYS_H_

# include "stdint.h"

/**
 * @brief Macro to access a single bit of a peripheral register (bit band region
 *        0x40000000 to 0x400FFFFF) using the bit-band alias region access.
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return Value of the targeted bit in the bit band region.
 */
#define BITBAND_REG(Reg,Bit) (*((uint32_t volatile*)(0x42000000u + (32u*((uint32_t)&(Reg) - (uint32_t)0x40000000u)) + (4u*((uint32_t)(Bit))))))
#define pBITBAND_REG(Reg,Bit) ((uint32_t volatile*)(0x42000000u + (32u*((uint32_t)&(Reg) - (uint32_t)0x40000000u)) + (4u*((uint32_t)(Bit)))))

extern void KEY_Scan(void);
extern void KEY_init(void);
extern uint32_t KEY_GetStatus(uint32_t index);
extern void Start_Check(void);

# endif
