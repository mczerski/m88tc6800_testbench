#include "common.h"
#include <stdlib.h>
#include <string.h>

uint32_t i2c_log[1000];
uint32_t expected_i2c_op = 0;
uint32_t actual_i2c_op = 0;
uint8_t i2c_reg[256];
char msg[1000];

void init() {
  expected_i2c_op = 0;
  actual_i2c_op = 0;
  memset(msg, 0, sizeof(msg));
}

void finish() {
    if (expected_i2c_op != actual_i2c_op) {
        printf("expected ops: %d, actual ops: %d\n", expected_i2c_op, actual_i2c_op);
        printf("%s", msg);
        exit(-1);
    }
}

void i2c_reg_fill(unsigned pattern) {
    static const uint8_t flat[] = {0x00, 0xff, 0xaa, 0x55};

    if (pattern < sizeof(flat)) {
        memset(i2c_reg, flat[pattern], sizeof(i2c_reg));
        return;
    }
    /* Deterministic pseudo-random fills -- two different seeds. */
    uint32_t s = 0x9e3779b9u * (pattern - sizeof(flat) + 1);
    for (size_t i = 0; i < sizeof(i2c_reg); i++) {
        s = s * 1103515245u + 12345u;
        i2c_reg[i] = (uint8_t)(s >> 16);
    }
}

uint32_t freq_start = 0;
uint32_t freq_stop = 1000000;
uint32_t freq_stride = 1;
uint32_t n_patterns = N_PATTERNS;

/* Every frequency the driver compares against, in kHz. */
static const uint32_t band_edges[] = {
    /* set_rf_frontend */
    112000, 334000, 366000, 374000, 451000, 480000, 492000,
    602000, 610000, 624000, 700000, 800000, 820000, 900000,
    /* set_mixer */
    125000, 167000, 250000, 330000, 335000, 400000,
    /* set_lo */
    56000, 63000, 83000, 333000, 500000, 666000, 667000,
    /* set_dac fixed-frequency special cases (0xf37ff, 0x79ac9) */
    996351, 498377,
    /* get_rf_power */
    110000, 110001, 200001, 334001, 400001, 475025, 600001,
    700001, 800001, 860001, 900001,
};

#define N_SPREAD 128
uint32_t freq_probes[3 * (sizeof(band_edges) / sizeof(band_edges[0])) + N_SPREAD + 4];
size_t n_freq_probes = 0;

static uint32_t env_u32(const char *name, uint32_t fallback) {
    const char *v = getenv(name);
    if (v == NULL || *v == '\0')
        return fallback;
    return (uint32_t)strtoul(v, NULL, 0);
}

static void probe_add(uint32_t freq) {
    if (freq >= 1000000)
        return;
    freq_probes[n_freq_probes++] = freq;
}

void suite_init() {
    freq_start = env_u32("FREQ_START", freq_start);
    freq_stop = env_u32("FREQ_STOP", freq_stop);
    freq_stride = env_u32("FREQ_STRIDE", freq_stride);
    n_patterns = env_u32("PATTERNS", n_patterns);
    if (freq_stride == 0)
        freq_stride = 1;
    if (n_patterns == 0 || n_patterns > N_PATTERNS)
        n_patterns = N_PATTERNS;

    probe_add(0);
    probe_add(1);
    probe_add(1000);
    for (size_t i = 0; i < sizeof(band_edges) / sizeof(band_edges[0]); i++) {
        probe_add(band_edges[i] - 1);
        probe_add(band_edges[i]);
        probe_add(band_edges[i] + 1);
    }
    /* 7817 is prime, so the spread lands on a different residue for every
     * spur spacing set_dac tests against (27000, 28200, 28350, 29700,
     * 30000, 32400) instead of aliasing onto one of them. */
    for (uint32_t f = 7817; f < 1000000; f += 7817)
        probe_add(f);
}
