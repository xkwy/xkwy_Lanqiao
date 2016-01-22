
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      TaskMgr.h
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-22
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __TASKMGR_H__
# define __TASKMGR_H__

# include "stdint.h"

typedef volatile struct {
    uint32_t TK_Timer;
    uint32_t TK_Period;
    uint32_t TK_Times;
    uint32_t TK_Enable;
    void (*pTK_Fun)(void);
} *pTask_t, Task_t;

extern void Task_init(pTask_t p, void (*f)(void), uint32_t dwPeriod, uint32_t dwTimes);
extern void Task_Check(pTask_t p);
extern void Task_Trig(pTask_t p);
extern void Task_Enable(pTask_t p);
extern void Task_Disable(pTask_t p);

extern void TK_NOP(void);

# endif
