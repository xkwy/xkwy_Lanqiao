
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
# include "TaskMgr.h"
# include "SystemTick.h"
# include "SoftwareDelay.h"

# include "keys.h"
# include "led.h"
# include "adc.h"
# include "lcd.h"
# include "at24c02.h"
# include "pwm.h"

extern const uint8_t PIC_SETTING[];
extern const uint8_t PIC_MAIN[2][320*240/8];
extern const uint8_t PIC_XKWY[];

static Task_t TK_Main[2];

static uint32_t out_freq;
static uint32_t out_enable = 1;
static uint32_t mode_setting = 0;

static void SER_PWMEnableUpdate(void)
{
    (out_enable ? LED_ON : LED_OFF)(LED_0);
    
    if (mode_setting) return ;
    
    LCD_DrawPicture(PIC_MAIN[out_enable]);
}

void TK_VoltRefresh(void)
{
    char s[40];
    double val;
    uint32_t wid;
    
    if (mode_setting) return ;
    
    val = ADC_GetVolt();
    sprintf(s, "%.2lfV  ", val);
    LCD_DisplayStringLine(Line3,130,(u8*)s);
    
    if (out_enable)
    {
        wid = (uint32_t)(100*val/3.3);
        PWM_Set(out_freq, wid);
        
        sprintf(s, "PA9: %d%%  ", wid);
        LCD_DisplayStringLine(Line6,130,(u8*)s);
        sprintf(s, "PB14:%d%%  ", 100-wid);
        LCD_DisplayStringLine(Line7,130,(u8*)s);
        sprintf(s, "%dKHz  ", out_freq);
        LCD_DisplayStringLine(Line8,130,(u8*)s);
    }
    else
    {
        PWM_Disable();
        
        LCD_DisplayStringLine(Line6,130,"PA9: -    ");
        LCD_DisplayStringLine(Line7,130,"PB14:-    ");
        LCD_DisplayStringLine(Line8,130,"- Hz   ");
    }
}

int main(void)
{
    Start_Check();
    
    delay_init();
    SystemTick_Run();
    
    KEY_init();
    LED_init();
    ADC_init();
    STM3210B_LCD_Init();
    AT24C02_init();
    PWM_init();
    
    LCD_DrawPicture(PIC_XKWY);
    for (int i = 0; i < 20; i++)
    {
        LCD_DisplayStringLine(Line0,16*i,"*");
        LCD_DisplayStringLine(Line9,304-16*i,"*");
        delay_ms(50);
    }
    
    AT24C02_Read(&out_freq, sizeof(out_freq), 0x10);
    if (out_freq != 0xAA55AA55)
    {
        out_freq = 0xAA55AA55;
        AT24C02_Write(&out_freq, sizeof(out_freq), 0x10);
        delay_ms(10);
        
        out_freq = 1;
        AT24C02_Write(&out_freq, sizeof(out_freq), 0x14);
        delay_ms(10);
    }
    AT24C02_Read(&out_freq, sizeof(out_freq), 0x14);
    
    SER_PWMEnableUpdate();
    
    Task_init(&TK_Main[0], KEY_Scan, 2, 0);
    Task_init(&TK_Main[1], TK_VoltRefresh, 100, 0);
    
    while (1)
    {
        Task_Check(&TK_Main[0]);
        Task_Check(&TK_Main[1]);
        
        __WFI();
    }
}

static void SER_SettingUpdate(void)
{
    char s[40];
    sprintf(s, "%dKHz  ", out_freq);
    LCD_DisplayStringLine(Line4,180,(u8*)s);
}

extern void KEY_EventDown(uint32_t i)
{
    switch (i)
    {
        case 0:
        {
            out_enable = out_enable ? 0 : 1;
            SER_PWMEnableUpdate();
            break;
        }
        case 1:
        {
            mode_setting = mode_setting ? 0 : 1;
            
            if (mode_setting)
            {
                LCD_DrawPicture(PIC_SETTING);
                SER_SettingUpdate();
            }
            else
            {
                AT24C02_Write(&out_freq, sizeof(out_freq), 0x14);
                SER_PWMEnableUpdate();
            }
            break;
        }
        case 2:
        {
            if (!mode_setting) return ;
            
            out_freq = (out_freq==10) ? 1 : out_freq+1;
            SER_SettingUpdate();
            break;
        }
        default :
        {
            break;
        }
    }
}

/* End Line */
