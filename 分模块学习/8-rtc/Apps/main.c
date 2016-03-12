
#include "stm32f10x.h"                  // Device header


# include "stdio.h"

void uart_init(u32);
void rtc_init(u8 h, u8 m, u8 s);



int main(void)
{
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    uart_init(38400);
    
    rtc_init(23, 59, 55);
    
    puts("Hello, xkwy.");
    
    while (1)
    {
        ;
    }
}




void rtc_up(u8 h, u8 m, u8 s)
{
    printf(" %02dh %02dm %02ds\r\n", h, m, s);
}




