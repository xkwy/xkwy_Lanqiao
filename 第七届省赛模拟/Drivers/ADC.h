
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

# define ADC_MAX        4000

extern void ADC_init(void);

extern double ADC_GetVolt(void);


# endif
