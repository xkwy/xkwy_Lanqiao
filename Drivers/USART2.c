
/******************************************************
 ***                                                 **
 ******************************************************
 * @file      usart2.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-22
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/


# include "stdint.h"
# include "stm32f10x.h"                  // Device header
# include "usart2.h"
# include "stdio.h"

void USART2_IRQHandler(void)
{
    if (BITBAND_REG(USART2->SR, 5))
    {
        USART2_SendByte(USART2->DR);
    }
}

extern void USART2_init(uint32_t dwBaudRate)
{
    uint32_t USART2_Clock;
    
    /* Calc peripheral clock */
    SystemCoreClockUpdate();
    if (RCC->CFGR & RCC_CFGR_PPRE1_2)
    {
        USART2_Clock = SystemCoreClock>>(((RCC->CFGR & RCC_CFGR_PPRE1)>>8)-3);
    }
    else
    {
        USART2_Clock = SystemCoreClock;
    }
    
    /* Enable AFIO Clock */
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    
    /* Disable USART2 Remap */
    AFIO->MAPR &= ~AFIO_MAPR_USART2_REMAP;
    
    /* Enable Port A Clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    
    /* PA2,PA3 as Alternate function */
    GPIOA->CRL &= ~((GPIO_CRL_MODE2|GPIO_CRL_CNF2)
                  | (GPIO_CRL_MODE3|GPIO_CRL_CNF3));
    GPIOA->CRL |= ((GPIO_CRL_MODE2|GPIO_CRL_CNF2_1) /* TX */
                 | (GPIO_CRL_CNF3_1));              /* RX */
    GPIOA->ODR |= (1<<3);                           /* pull-up */
    
    /* Enable USART2 Clock */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    /* Reset USART2 */
    RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
    
    /* Calc Baud rate according to the peripheral clock */
    USART2->BRR = USART2_Clock / dwBaudRate;
    
    USART2->CR1 = USART_CR1_UE
                | USART_CR1_RXNEIE
                | USART_CR1_TE
                | USART_CR1_RE;
    
    NVIC_EnableIRQ(USART2_IRQn);
}


extern void USART2_SendByte(uint8_t by)
{
    while (!BITBAND_REG(USART2->SR, 7));
    USART2->DR = by;
}

extern void USART2_SendBytes(uint8_t *pby, uint32_t n)
{
    while (n--)
    {
        USART2_SendByte(*pby++);
    }
}

extern void USART2_SendHex(uint8_t *pby, uint32_t n)
{
    const char HEX_CODE[] = "0123456789ABCDEF";
    
    while (n--)
    {
        USART2_SendByte(HEX_CODE[(*pby)>>4]);
        USART2_SendByte(HEX_CODE[(*pby)&0xF]);
        USART2_SendByte(' ');
        *pby++;
    }
}

extern void USART2_SendString(char *s)
{
    while (*s)
    {
        USART2_SendByte(*s++);
    }
}

int fputc(int ch, FILE *f)
{
    USART2_SendByte(ch);
    
    return ch;
}

/* End Line */
