
#include "stm32f10x.h"                  // Device header


void tim_init(u32);
void pwm_set(u32);

vu32 tick = 0;

# define P  200

int main(void)
{
    u32 v;
    u32 t1 = 0;
    
    RCC->APB2ENR = 0x3D;
    while (1&~GPIOA->IDR);
    
    
    SysTick_Config(72000);
    
    tim_init(P);
    
    
    while (1)
    {
        if (tick-t1 >= 25)
        {
            t1 = tick;
            
            pwm_set(++v % P);
        }
        
        __WFI();
    }
}








void SysTick_Handler(void)
{
    tick++;
}
