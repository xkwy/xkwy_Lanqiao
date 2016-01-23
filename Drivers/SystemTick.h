
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      SystemTick.h
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-22
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __SYSTEM_TICK_H_
# define __SYSTEM_TICK_H_

# include "stdint.h"

extern void SystemTick_Run(void);


static __inline uint32_t GetTickCount(void)
{
    extern volatile uint32_t SysTickCount;

    return SysTickCount;
}


# endif
