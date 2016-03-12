#include "stm32f10x.h"                  // Device header

# include "stdio.h"

char buf[80];
u32 i = 0;

void UART_Get(char *s);

void USART2_IRQHandler(void)
{
    if ('\n' == (buf[i++]=USART2->DR))
    {
        buf[i] = '\0';
        i = 0;
        UART_Get(buf);
    }
}

void UART_init(u32 brd)
{
    GPIOA->CRL ^= 0xF00;
    
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    USART2->BRR = 36000000 / brd;
    
    USART2->CR1 = 0x202C;
    
    NVIC_EnableIRQ(USART2_IRQn);
}


int fputc(int ch, FILE *p)
{
    USART2->DR = ch;
    while ((1<<7)&~USART2->SR);
    
    return ch;
}


