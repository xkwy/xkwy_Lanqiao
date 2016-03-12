
#include "stm32f10x.h"                  // Device header
# include "stdio.h"

void adc_init(void);
u32 adc_get(void);
void uart_init(u32 brd);

int main(void)
{
    u32 val;
    
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    adc_init();
    uart_init(38400);
    
    GPIOC->CRH = 0x33333333;
    
    while (1)
    {
        val = adc_get();
        GPIOC->ODR = 0xFF<<(val>>9);
        
        for (uint32_t i = 0; i < 500000; i++);
        
        printf(" adc val: %d.\r\n", val);
    }
}

