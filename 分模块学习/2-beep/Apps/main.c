

#include "stm32f10x.h"                  // Device header

# define BITBAND(Reg, Bit) (*(vu32*)(0x42000000 + 32*((u32)&Reg - 0x40000000) + 4*(Bit)))

void BEEP_init(void);


int main(void)
{
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    BEEP_init();
    
    
    while (1)
    {
        BITBAND(GPIOB->ODR, 4) = 0; for (u32 i = 0; i < 500000; i++);
        BITBAND(GPIOB->ODR, 4) = 1; for (u32 i = 0; i < 50*500000; i++);
    }
}

