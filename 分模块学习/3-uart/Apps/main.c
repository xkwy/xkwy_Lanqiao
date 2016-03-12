
#include "stm32f10x.h"                  // Device header

# include "stdio.h"

void UART_init(u32 brd);






int main(void)
{
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    UART_init(38400);
    
    printf("PAx:yyy\r\n");
    
    while (1)
    {
        ;
    }
}


void UART_Get(char *s)
{
    u32 a, b;
    if (2 == sscanf(s, "PA%1d:%d", &a, &b))
    {
        printf("Got Packed: x=%d, y=%d.\r\n", a, b);
    }
    else
    {
        printf("Error Format!\r\n");
    }
}
