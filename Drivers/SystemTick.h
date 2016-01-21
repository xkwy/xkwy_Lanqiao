
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      SystemTick.h
 * @author    xkwy
 * @version   V1.00
 * @date      2015-12-19
 ******************************************************
 * @attention
 *
 * Copyright (C) 2015 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __SYSTEM_TICK_H_
# define __SYSTEM_TICK_H_

extern void SystemTick_Run(void);


static __inline uint32_t GetTickCount(void)
{
    extern volatile uint32_t SysTickCount;

    return SysTickCount;
}


# endif
