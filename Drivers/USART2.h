
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      SoftwareDelay.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-22
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/


# ifndef __STM32_USART2_H_
# define __STM32_USART2_H_

# include "stdint.h"

/**
 * @brief Macro to access a single bit of a peripheral register (bit band region
 *        0x40000000 to 0x400FFFFF) using the bit-band alias region access.
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return Value of the targeted bit in the bit band region.
 */
#define BITBAND_REG(Reg,Bit) (*((uint32_t volatile*)(0x42000000u + (32u*((uint32_t)&(Reg) - (uint32_t)0x40000000u)) + (4u*((uint32_t)(Bit))))))

void USART2_init(uint32_t dwBaudRate);
void USART2_SendByte(uint8_t by);
void USART2_SendBytes(uint8_t *pby, uint32_t n);
void USART2_SendHex(uint8_t *pby, uint32_t n);
void USART2_SendString(char *s);


# endif

