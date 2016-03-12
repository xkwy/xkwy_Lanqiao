
#include "stm32f10x.h"                  // Device header
# include "stdio.h"

void UART_init(u32);
void KEY_scan(void);
vu32 tick = 0;

void SysTick_Handler(void)
{
    tick++;
}


int main(void)
{
    u32 tk0 = 0;
    u32 tk1 = 0;
    
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    SysTick_Config(72000);
    UART_init(38400);
    
    while (1)
    {
        if (tick-tk0 >= 2)
        {
            tk0 = tick;
            KEY_scan();
        }
        if (tick-tk1 >= 6000)
        {
            tk1 = tick;
            printf("[tick] ");
        }
        __WFI();
    }
}


void KEY_Down(u32 i)
{
    putchar("xkwy"[i]);
}








