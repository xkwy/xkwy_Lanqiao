
#include "stm32f10x.h"                  // Device header

# define BITBAND(Reg, Bit)      (*((vu32*)(0x42000000 + 32*((u32)&(Reg)-0x40000000) + 4*(Bit))))

# define SCLO       BITBAND(GPIOB->ODR, 6)
# define SDAO       BITBAND(GPIOB->ODR, 7)

# define SDAI       BITBAND(GPIOB->IDR, 7)

void delay(void)
{
    u32 i;
    for (i = 0; i < 10; i++);
}

void EE_init(void)
{
    GPIOB->CRL ^= 0x33000000;
}

void _start(void)
{
    SCLO = 0; delay();
    SDAO = 1; delay();
    SCLO = 1; delay();
    SDAO = 0; delay();
    SCLO = 0; delay();
}

void _write(u8 d)
{
    s32 i;
    
    for (i = 7; i >= 0; i--)
    {
        SDAO = d >> i;
        SCLO = 1; delay();
        SCLO = 0; delay(); 
    }
    
    SDAO = 1; delay();
    SCLO = 1; delay();
    SCLO = 0; delay();
}

u8 _read(void)
{
    s32 i;
    u8 re = 0x00;
    
    SDAO = 1; delay();
    for (i = 7; i >= 0; i--)
    {
        SCLO = 1; delay();
        re |= SDAI << i;
        SCLO = 0; delay();
    }
    
    SDAO = 1; delay();
    SCLO = 1; delay();
    SCLO = 0; delay();
    
    return re;
}

void _stop(void)
{
    SCLO = 0; delay();
    SDAO = 0; delay();
    SCLO = 1; delay();
    SDAO = 1; delay();
}

u8 ee_read(u8 addr)
{
    u8 re;
    _start();
    _write(0xA0);
    _write(addr);
    _start();
    _write(0xA1);
    re = _read();
    _stop();
    
    return re;
}

void ee_write(u8 addr, u8 dt)
{
    _start();
    _write(0xA0);
    _write(addr);
    _write(dt);
    _stop();
}
