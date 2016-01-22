
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

# include "keys.h"
# include "beep.h"
# include "led.h"


static Task_t TK_Main[8];


void TK_test(void)
{
    printf("#");
    BEEP_Set(150);
    LED_TOG(LED_2);
}

int main(void)
{
    Start_Check();
    
    delay_init();
    SystemTick_Run();
    USART2_init(38400);
    
    KEY_init();
    BEEP_init();
    LED_init();
    
    Task_init(&TK_Main[0], KEY_Scan, 2, 0);
    Task_init(&TK_Main[1], BEEP_Scan, 1, 0);
    Task_init(&TK_Main[2], TK_NOP, 1000, 0);
    Task_init(&TK_Main[3], TK_NOP, 1000, 0);
    Task_init(&TK_Main[4], TK_NOP, 1000, 0);
    Task_init(&TK_Main[5], TK_NOP, 1000, 0);
    Task_init(&TK_Main[6], TK_NOP, 1000, 0);
    Task_init(&TK_Main[7], TK_test, 3000, 0);
    
    LED_ON(LED_0);
    Task_Trig(&TK_Main[7]);
    
    while (1)
    {
        Task_Check(&TK_Main[0]);
        Task_Check(&TK_Main[1]);
        Task_Check(&TK_Main[2]);
        Task_Check(&TK_Main[3]);
        Task_Check(&TK_Main[4]);
        Task_Check(&TK_Main[5]);
        Task_Check(&TK_Main[6]);
        Task_Check(&TK_Main[7]);
        
        __WFI();
    }
}

extern void KEY_EventUp(uint32_t i)
{
    LED_OFF((LED_t)(16<<i));
    printf(" the KEY of 'B%d' UP!!\r\n", i+1);
}

extern void KEY_EventDown(uint32_t i)
{
    LED_ON((LED_t)(16<<i));
    BEEP_Set(50);
    printf(" the KEY of 'B%d' Down!!\r\n", i+1);
}

/* End Line */
