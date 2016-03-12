
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
# include "led.h"
# include "adc.h"
# include "lcd.h"
# include "at24c02.h"
# include "rtc.h"

static Task_t TK_Main[8];

static uint32_t val_k;
static uint32_t led_en = 1;
static uint32_t mode_setting = 0;
static uint32_t up_time[3] ={0, 0, 0};

void TK_LED_TOG(void) {LED_TOG(LED_0);}

extern void SER_KSetUpdate(void)
{
    char str[40];
    
    if (mode_setting) return ;
    
    sprintf(str, " k: 0.%d  ", val_k);
    LCD_DisplayStringLine(Line3,(u8*)str);
}

extern void SER_LEDSetUpdate(void)
{
    char str_tmp[40];
    
    sprintf(str_tmp, " LED: O%s", led_en ? "N " : "FF");
    LCD_DisplayStringLine(Line5,(u8*)str_tmp);
}

void SER_TimeSetUpdate(void)
{
    char s_tmp[40];
    
    sprintf(s_tmp, "     %02d-%02d-%02d", up_time[2], up_time[1], up_time[0]);
    LCD_DisplayStringLine(Line4,(u8*)s_tmp);
}

extern void RTC_Update(uint32_t h, uint32_t m, uint32_t s)
{
    char str[40];
    
    if (mode_setting) return ;
    
    sprintf(str, " T: %02d-%02d-%02d", h, m, s);
    LCD_DisplayStringLine(Line7,(u8*)str);
    
    if ((h==up_time[2]) && (m==up_time[1]) && (s==up_time[0]))
    {
        printf("%.2lf+0.%d+%02d%02d%02d\n",ADC_GetVolt(),val_k,h,m,s);
    }
}

void TK_VoltRefresh(void)
{
    char s_tmp[40];
    double val = ADC_GetVolt();
    
    if ((val>0.33*val_k) && led_en)
    {
        Task_Enable(&TK_Main[1]);
    }
    else
    {
        Task_Disable(&TK_Main[1]);
        LED_OFF(LED_0);
    }
    
    if (mode_setting) return ;
    
    sprintf(s_tmp, " V1: %.2lfV  ", val);
    LCD_DisplayStringLine(Line1,(u8*)s_tmp);
}

int main(void)
{
    Start_Check();
    
    delay_init();
    SystemTick_Run();
    USART2_init(9600);
    
    KEY_init();
    LED_init();
    ADC_init();
    STM3210B_LCD_Init();
    AT24C02_init();
    RTC_init(23,59,55);
    
    AT24C02_Read(&val_k, sizeof(val_k), 0x00);
    if (val_k != 0xAA5555AA)
    {
        val_k = 0xAA5555AA;
        AT24C02_Write(&val_k, sizeof(val_k), 0x00);
        delay_ms(10);
        
        val_k = 1;
        AT24C02_Write(&val_k, sizeof(val_k), 0x04);
        delay_ms(10);
    }
    AT24C02_Read(&val_k, sizeof(val_k), 0x04);
    
    SER_KSetUpdate();
    SER_LEDSetUpdate();
    
    Task_init(&TK_Main[0], KEY_Scan, 2, 0);
    Task_init(&TK_Main[1], TK_LED_TOG, 200, 0);
    Task_init(&TK_Main[2], TK_VoltRefresh, 100, 0);
    
    while (1)
    {
        Task_Check(&TK_Main[0]);
        Task_Check(&TK_Main[1]);
        Task_Check(&TK_Main[2]);
        
        __WFI();
    }
}

extern void USART2_GetPacket(char *s)
{
    uint32_t v;
    
    if (1 == sscanf(s, "k0.%1d", &v))
    {
        if (v-1 < 9)
        {
            val_k = v;
            
            AT24C02_Write(&val_k, sizeof(val_k), 0x04);
            SER_KSetUpdate();
            printf("ok\n");
        }
    }
}

extern void KEY_EventDown(uint32_t i)
{
    static uint32_t curr = 0;
    const char *LCD_CURR[] = {"            *","         *   ","      *      "};
    
    switch (i)
    {
        case 0:
        {
            if (mode_setting) return ;
            
            led_en = led_en ? 0 : 1;
            SER_LEDSetUpdate();
            
            break;
        }
        case 1:
        {
            mode_setting = mode_setting ? 0 : 1;
            
            LCD_Clear(White);
            if (mode_setting)
            {
                LCD_DisplayStringLine(Line2,(u8*)"      Setting");
                
                SER_TimeSetUpdate();
                LCD_DisplayStringLine(Line5,(u8*)LCD_CURR[curr]);
            }
            else
            {
                SER_KSetUpdate();
                SER_LEDSetUpdate();
            }
            
            break;
        }
        case 2:
        {
            if (!mode_setting) return ;
            
            curr = (curr+1) % 3;
            LCD_DisplayStringLine(Line5,(u8*)LCD_CURR[curr]);
            
            break;
        }
        case 3:
        {
            if (!mode_setting) return ;
            
            up_time[curr] = (up_time[curr]+1) % 60;
            if (curr == 2) up_time[2] %= 24;
            
            SER_TimeSetUpdate();
            
            break;
        }
        default:
        {
            break;
        }
    }
}

/* End Line */
