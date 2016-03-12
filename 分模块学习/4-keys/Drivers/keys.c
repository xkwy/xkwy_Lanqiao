

#include "stm32f10x.h"                  // Device header

void KEY_Down(u32);

# define BITBAND(Reg, Bit) (*((vu32*)(0x42000000+32*((u32)&(Reg)-0x40000000)+4*(Bit))))

u32 stu[4];
u32 his[4];

void KEY_scan(void)
{
    u32 i;
    
    his[0] |= BITBAND(GPIOA->IDR, 0);
    his[1] |= BITBAND(GPIOA->IDR, 8);
    his[2] |= BITBAND(GPIOB->IDR, 1);
    his[3] |= BITBAND(GPIOB->IDR, 2);
    
    for (i = 0; i < 4; i++)
    {
        if (stu[i] &&! his[i]) KEY_Down(i);
        
        stu[i] = his[i];
        his[i] <<= 1;
    }
}



