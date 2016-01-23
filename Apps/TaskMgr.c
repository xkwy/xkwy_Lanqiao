
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      TaskMgr.c
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
# include "TaskMgr.h"
# include "SystemTick.h"

extern __attribute__((weak)) void TK_NOP(void)
{
    __nop(); __nop(); __nop(); __nop();
}

extern void Task_init(pTask_t p, void (*f)(void), uint32_t dwPeriod, uint32_t dwTimes)
{
    p->TK_Timer = GetTickCount();
    p->TK_Period = dwPeriod;
    p->pTK_Fun = f;
    p->TK_Times = dwTimes;
    Task_Enable(p);
}

extern void Task_Check(pTask_t p)
{
    if (p->TK_Enable)
    {
        if (GetTickCount() >= p->TK_Timer + p->TK_Period)
        {
            p->TK_Timer = GetTickCount();
            p->pTK_Fun();
            if (p->TK_Times > 1) p->TK_Times--;
            else if (p->TK_Times == 1) p->TK_Enable = 0;
        }
    }
}

extern void Task_Trig(pTask_t p)
{
    p->TK_Timer = GetTickCount();
    p->pTK_Fun();
}

extern void Task_Enable(pTask_t p)
{
    p->TK_Enable = 1;
}

extern void Task_Disable(pTask_t p)
{
    p->TK_Enable = 0;
}

/* End Line */
