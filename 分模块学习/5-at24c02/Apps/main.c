
#include "stm32f10x.h"                  // Device header

# include "stdio.h"

void UART_init(u32 brd);

void EE_init(void);
u8 ee_read(u8 addr);
void ee_write(u8 addr, u8 dt);

# define ADDR 0xFF

int main(void)
{
    u8 i;
    
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    UART_init(38400);
    EE_init();
    
    i = ee_read(ADDR);
    printf("Hello? i=%d\r\n", i++);
    ee_write(ADDR, i);
    while (1)
    {
        ;
    }
}


