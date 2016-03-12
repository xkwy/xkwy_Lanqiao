
#include "stm32f10x.h"                  // Device header


# include "stdio.h"

void uart_init(u32);
void rtc_init(u8 h, u8 m, u8 s);



int main(void)
{
    u32 t, val;
    
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    uart_init(38400);
    
    rtc_init(23, 59, 55);
    
    puts("Hello, xkwy.");
    
    while (1)
    {
        for (t = 0; t < 500000; t++);
        
        val = ((RTC->CNTH<<16) + RTC->CNTL) % (24*3600);
        printf(" %02dh %02dm %02ds\r\n", val/3600, val/60%60, val%60);
    }
}

