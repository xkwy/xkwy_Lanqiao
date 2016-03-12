
#include "stm32f10x.h"                  // Device header
# include "stdio.h"

void adc_init(void);

void uart_init(u32 brd);
u32 adc_get_r(void);
u32 adc_get_t(void);
u32 adc_get_v(void);

int main(void)
{
    u32 r, t, v;
    double temp;
    
    RCC->APB2ENR = 0x3D;
    while (1 &~ GPIOA->IDR);
    
    adc_init();
    uart_init(38400);
    
    GPIOC->CRH = 0x33333333;
    
    while (1)
    {
        r = adc_get_r();
        t = adc_get_t();
        v = adc_get_v();
        
        GPIOC->ODR = 0xFF<<(r/512);
        
        temp = 1000.0*(1.43-1.2*t/v)/4.3 + 25.0;
        
        printf("R:%.2lf%%, T:%.2lf C, VCC:%.2lfV\r\n", r/40.96, temp, 1.2*4096/v);
        
        for (uint32_t i = 0; i < 500000; i++);
    }
}

