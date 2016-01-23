
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      adc.h
 * @author    xkwy
 * @version   V1.00
 * @date      2016-1-23
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __ADC_H_
# define __ADC_H_

# include "stdint.h"


extern void ADC_init(void);
extern void ADC_GetVal(uint32_t *dt);

extern uint32_t ADC_GetRes(void);
extern uint32_t ADC_GetTemp(void);


# endif
