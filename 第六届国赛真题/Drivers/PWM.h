
/******************************************************
 ***  the 7th 'LanQiao' Cup Embedded Training Board  **
 ******************************************************
 * @file      pwm.c
 * @author    xkwy
 * @version   V1.00
 * @date      2016-2-4
 ******************************************************
 * @attention
 *
 * Copyright (C) 2016 xkwy LIMITED
 * All rights reserved.
 ******************************************************/

# ifndef __STM32_PWM_H_
# define __STM32_PWM_H_

# include "stdint.h"

extern void PWM_init(void);
extern void PWM_Set(uint32_t freq, uint32_t wid);
extern void PWM_Disable(void);


# endif
