
#include "stm32f10x.h"                  // Device header

# include "stdio.h"

void uart_init(u32 b)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    GPIOA->CRL ^= 0xF00;
    
    USART2->CR1 = 0x202C;
    
    USART2->BRR = 36000000 / b;
}


int fputc(int ch, FILE *f)
{
    USART2->DR = ch;
    while ((1<<7) & ~USART2->SR);
    
    return ch;
}
