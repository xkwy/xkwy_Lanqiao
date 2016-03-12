
#include "stm32f10x.h"                  // Device header
# include "stdio.h"

void UART_init(u32 brd)
{
    GPIOA->CRL ^= 0xF00;
    
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    USART2->CR1 = 0x202C;
    
    USART2->BRR = 36000000 / brd;
}

int fputc(int ch, FILE *f)
{
    USART2->DR = ch;
    
    while ((1<<7)&~USART2->SR);
    
    return ch;
}
