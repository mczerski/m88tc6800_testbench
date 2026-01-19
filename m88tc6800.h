#ifndef __M88TC6800_H__
#define __M88TC6800_H__

#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//TODO: remove
#include "gtm_hardware_fe.ko.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s32 int32_t
#define msleep(ms)

struct i2c_adapter {};

struct m88tc6800_config {
	u8 addr;
	u32 xtal;
	u8 xtal_cap;
	u8 mode;
	u8 int_lt;
	u8 int_im;
	u8 custom_cfg;
	u8 harmonic_imp;
	u8 dac_gain;
	u32 dac;
};

#endif //__M88TC6800_H__
