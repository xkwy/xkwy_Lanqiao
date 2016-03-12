
#include "stm32f10x.h"                  // Device header
# include "stdio.h"


void uart_init(u32);
void ee_init(void);
u8 ee_read(u8 addr);
void ee_write(u8 addr, u8 dt);

# define ADDR    0xff

int main(void)
{
    u8 cnt;
    
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    uart_init(38400);
    ee_init();
    
    cnt = ee_read(ADDR);
    
    printf("Hello cnt = %d\r\n", cnt++);
    ee_write(ADDR, cnt);
    
    while (1)
    {
        ;
    }
}


