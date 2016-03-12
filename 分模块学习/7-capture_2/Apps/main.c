
#include "stm32f10x.h"                  // Device header
# include "stdio.h"


void uart_init(u32 b);


u32 tick = 0;


void cap_init(void);
void tim_init(u32 f);
void tim_set(u32 p);
extern u32 wid;
extern u32 pp;


int main(void)
{
    u32 t0 = 0;
    u32 t1 = 0;
    u32 p;
    
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    SysTick_Config(72000);
    
    uart_init(38400);
    tim_init(2);
    cap_init();
    
    printf("Hello ");
    
    while (1)
    {
        if (tick-t0 >= 200)
        {
            t0 = tick;
            
            p = ++p%100;
            tim_set(p);
            printf("\r\n- p is set to %d %% >", p);
        }
        if (tick-t1 >= 20)
        {
            t1 = tick;
            
            printf(" %.1lf%%", 100.0*pp/wid);
            wid = pp = 0;
        }
        __wfi();
    }
}




void SysTick_Handler(void)
{
    tick++;
}
