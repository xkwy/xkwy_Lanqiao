
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

# include "stdio.h"
# include "stdint.h"
# include "usart2.h"
# include "TaskMgr.h"
# include "SystemTick.h"
# include "SoftwareDelay.h"


static Task_t TK_Main[9];


void TK_test(void)
{
    printf("Hello? World! xkwy.\r\n");
}

int main(void)
{
    delay_init();
    SystemTick_Run();
    USART2_init(38400);
    
    
    Task_init(&TK_Main[0], TK_test, 500, 0);
    
    while (1)
    {
        Task_Check(&TK_Main[0]);
        
        __WFI();
    }
}

/* End Line */
