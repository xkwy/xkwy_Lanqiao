
#include "stm32f10x.h"                  // Device header



void LED_init(void);
void LED_Set(u8 v);

int main(void)
{
    RCC->APB2ENR = 0x3D;
    while (1&~GPIOA->IDR);
    
    LED_init();
    
    while (1)
    {
        LED_Set(0xAA); for (u32 i = 0; i < 1000000; i++);
        LED_Set(0x55); for (u32 i = 0; i < 1000000; i++);
    }
}
