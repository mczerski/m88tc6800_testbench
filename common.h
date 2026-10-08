#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

extern uint32_t i2c_log[];
extern uint32_t expected_i2c_op;
extern uint32_t actual_i2c_op;
extern uint8_t i2c_reg[];
extern char msg[];

void init();
void finish();

/* ------------------------------------------------------------------ *
 * Register read-back backgrounds
 *
 * The mock read path returns i2c_reg[reg] to both implementations. Any
 * register no runner assigns reads back as 0, which makes every
 * read-modify-write degenerate to (0 & ~mask) | val -- a wrong bit-field
 * mask then looks exactly like a right one. i2c_reg_fill() puts a
 * non-trivial background in the whole array; runners call it first and
 * then assign the registers they sweep explicitly.
 * ------------------------------------------------------------------ */
#define N_PATTERNS 6
void i2c_reg_fill(unsigned pattern);

/* ------------------------------------------------------------------ *
 * Sweep bounds. Overridable from the environment so the same runner can
 * serve as a fast pre-commit gate and as an exhaustive run:
 *   FREQ_START / FREQ_STOP / FREQ_STRIDE / PATTERNS
 * ------------------------------------------------------------------ */
extern uint32_t freq_start;
extern uint32_t freq_stop;
extern uint32_t freq_stride;
extern uint32_t n_patterns;

/* Frequencies worth testing when the dimension being swept is something
 * other than frequency: every band edge that appears in the driver plus
 * its +-1 neighbours, and a coarse spread over the whole range (the
 * spread matters because set_dac selects its ADC rate by freq modulo a
 * spur spacing, so band edges alone do not reach every branch). */
extern uint32_t freq_probes[];
extern size_t n_freq_probes;

/* Reads the environment and builds freq_probes[]. Call first in main(). */
void suite_init();
