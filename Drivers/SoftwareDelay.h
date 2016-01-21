
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      SoftwareDelay.h
 * @author    xkwy
 * @version   V1.00
 * @date      2015-12-19
 ******************************************************
 * @attention
 *
 * Copyright (C) 2015 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __SOFTWARE_DELAY_H__
# define __SOFTWARE_DELAY_H__

# include "stdint.h"

extern void delay_init(void);
extern void delay_us(const uint32_t);
extern void delay_ms(const uint32_t);

# endif
