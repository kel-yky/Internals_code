#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "lcd_blue.h"
#include "ticks.h"

#define ENCODER_INIT_COUNT     32767
#define ENCODER_MAX_COUNT      65535

void encoder_init(void);
void encoder_update(void);
s32 encoder_count(int encoder);
s32 enc_get_vel(int encoder);
void encoder_reset(void);

#endif		/*  __ENCODER_H */
