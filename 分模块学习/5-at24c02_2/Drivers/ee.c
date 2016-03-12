
#include "stm32f10x.h"                  // Device header

# define BITBAND(Reg, Bit)      (*((vu32*)(0x42000000 + 32*((u32)&(Reg)-0x40000000) + 4*(Bit))))

# define SCLO   BITBAND(GPIOB->ODR, 6)
# define SDAO   BITBAND(GPIOB->ODR, 7)
# define SDAI   BITBAND(GPIOB->IDR, 7)

void _delay(void)
{
    ;
}

void _start(void)
{
    SCLO = 0; _delay();
    SDAO = 1; _delay();
    SCLO = 1; _delay();
    SDAO = 0; _delay();
    SCLO = 0; _delay();
}

u8 _rw(u8 d)
{
    s32 i = 8;
    u8 re = 0x00;
    
    while (i--)
    {
        SDAO = d >> i; _delay();
        SCLO = 1; _delay();
        re |= SDAI << i;
        SCLO = 0; _delay();
    }
    
    SDAO = 1; _delay();
    SCLO = 1; _delay();
    SCLO = 0; _delay();
    
    return re;
}

void _stop(void)
{
    SCLO = 0; _delay();
    SDAO = 0; _delay();
    SCLO = 1; _delay();
    SDAO = 1; _delay();
}

void ee_init(void)
{
    GPIOB->CRL |= 0x33000000;
}

u8 ee_read(u8 addr)
{
    u8 re;
    
    _start();
    _rw(0xA0);
    _rw(addr);
    _start();
    _rw(0xA1);
    re = _rw(0xFF);
    _stop();
    
    return re;
}

void ee_write(u8 addr, u8 dt)
{
    _start();
    _rw(0xA0);
    _rw(addr);
    _rw(dt);
    _stop();
}
