


#include "stm32f10x.h"                  // Device header



void BEEP_init(void)
{
    AFIO->MAPR |= (1<<24);
    
    GPIOB->CRL ^= 0xF0000;
}
