
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      SystemTick.c
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
# include "stm32f10x.h"
# include "SystemTick.h"

volatile uint32_t SysTickCount;

void SysTick_Handler(void)
{
    SysTickCount++;
}

extern void SystemTick_Run(void)
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000UL);
    
    SysTickCount = 0x00000000UL;
}

/* End Line */
