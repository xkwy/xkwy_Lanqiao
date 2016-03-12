
#include "stm32f10x.h"                  // Device header
# include "stdio.h"


void uart_init(u32 b);


u32 tick = 0;


void cap_init(void);
void tim_init(void);
void tim_set(u32 f_khz);
extern u32 wid;

int main(void)
{
    u32 t0 = 0;
    u32 t1 = 0;
    u32 f = 1;
    
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    SysTick_Config(72000);
    
    uart_init(38400);
    tim_init();
    cap_init();
    
    printf("Hello ");
    tim_set(f);
    while (1)
    {
        if (tick-t0 >= 3000)
        {
            t0 = tick;
            
            f = f+1>10 ? 1 : f+1;
            tim_set(f);
            printf("---now freq is set to %d kHz.\r\n", f);
        }
        if (tick-t1 >= 500)
        {
            t1 = tick;
            
            printf("Freq = %.3lf Hz \r\n", 72000000.0/wid);
            wid = 0;
            ;
        }
        __wfi();
    }
}




void SysTick_Handler(void)
{
    tick++;
}
