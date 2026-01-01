#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern uint32_t i2c_log[];
extern uint32_t expected_i2c_op;
extern uint32_t actual_i2c_op;
extern uint8_t i2c_reg[];

void init();
void finish();
