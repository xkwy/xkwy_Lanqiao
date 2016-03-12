


#include "stm32f10x.h"                  // Device header

# define BITBAND(Reg, Bit) (*((vu32*)(0x42000000+32*((u32)&Reg-0x40000000)+4*(Bit))))


void LED_init(void)
{
    GPIOC->CRH = 0x33333333;
    
    GPIOD->CRL ^= 0x700;
}

void LED_Set(u8 v)
{
    GPIOC->ODR = v << 8;
    BITBAND(GPIOD->ODR, 2) = 1;
    BITBAND(GPIOD->ODR, 2) = 0;
}



