
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
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
# include "adc.h"
# include "lcd.h"
# include "at24c02.h"

static Task_t TK_Main[8];

static char s_tmp[40];

static uint32_t TimeBase = 0;
static uint32_t TimeTotal = 0;

void TK_test(void)  /* 6s */
{
    LED_TOG(LED_2);
    BEEP_Set(150);
    
    AT24C02_Write(&TimeTotal, sizeof(TimeTotal), 0x00);
    
    printf("Res:%6.1lf %%    ", (1000-ADC_GetRes())/10.0);
    printf("Temp: %6.2lf *C   ", ADC_GetTemp()/1000.0);
    
    printf("\r\n");
}

void TK_Timer(void) /* 100ms */
{
	LCD_SetTextColor(Blue2);
    TimeTotal = TimeBase + GetTickCount()/100;
    sprintf(s_tmp, "  Time: %08.1lf s  ", TimeTotal/10.0);
	LCD_DisplayStringLine(Line7,(u8*)s_tmp);
	LCD_SetTextColor(Black);
}

void TK_Info(void)  /* 200ms */
{
	LCD_SetTextColor(Black);
    sprintf(s_tmp, " $ Res: %.1lf%%  ", (1000-ADC_GetRes())/10.0);
	LCD_DisplayStringLine(Line2,(u8*)s_tmp);
    sprintf(s_tmp, " $ Temp: %.2lfC  ", ADC_GetTemp()/1000.0);
	LCD_DisplayStringLine(Line3,(u8*)s_tmp);
	LCD_SetTextColor(Black);
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
    ADC_init();
    STM3210B_LCD_Init();
    AT24C02_init();
    
    AT24C02_Read(&TimeBase, sizeof(TimeBase), 0x00);
    TimeTotal = TimeBase;
    
	LCD_SetTextColor(Black);
	LCD_SetBackColor(White);
	LCD_Clear(White);
    
	LCD_SetTextColor(Red);
	LCD_DisplayStringLine(Line0," -- Hello, xkwy. -- ");
	LCD_SetTextColor(Cyan);
	LCD_DisplayStringLine(Line8," * Compiled Time *  ");
	LCD_DisplayStringLine(Line9,__TIME__ " " __DATE__);
    
    Task_init(&TK_Main[0], KEY_Scan, 2, 0);
    Task_init(&TK_Main[1], BEEP_Scan, 1, 0);
    Task_init(&TK_Main[2], TK_Timer, 100, 0);
    Task_init(&TK_Main[3], TK_Info, 200, 0);
    Task_init(&TK_Main[4], TK_NOP, 1000, 0);
    Task_init(&TK_Main[5], TK_NOP, 1000, 0);
    Task_init(&TK_Main[6], TK_NOP, 1000, 0);
    Task_init(&TK_Main[7], TK_test, 6000, 0);
    
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
    printf(" the KEY of 'B%d' Up!!\r\n", i+1);
    
	LCD_SetTextColor(Yellow);
    sprintf(s_tmp, " + KEY_B%d Up!   ", i+1);
	LCD_DisplayStringLine(Line5,(u8*)s_tmp);
	LCD_SetTextColor(Black);
}

extern void KEY_EventDown(uint32_t i)
{
    BEEP_Set(50);
    LED_ON((LED_t)(16<<i));
    printf(" the KEY of 'B%d' Down!!\r\n", i+1);
    
	LCD_SetTextColor(Magenta);
    sprintf(s_tmp, " + KEY_B%d Down! ", i+1);
	LCD_DisplayStringLine(Line5,(u8*)s_tmp);
	LCD_SetTextColor(Black);
}

/* End Line */
