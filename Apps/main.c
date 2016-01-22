
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      main.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-21
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# include "stm32f10x.h"                  // Device header

# include "stdint.h"
# include "TaskMgr.h"
# include "SystemTick.h"
# include "SoftwareDelay.h"

static Task_t TK_Main[9];

void TK_test(void)
{
    ;
}

int main(void)
{
    delay_init();
    SystemTick_Run();
    
    Task_init(&TK_Main[0], TK_test, 500, 0);
    
    while (1)
    {
        Task_Check(&TK_Main[0]);
        
        __WFI();
    }
}






