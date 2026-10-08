#include "common.h"
#include "original.h"
#include "new.h"

static void run_case(uint32_t dac, uint8_t dac_gain, uint32_t bw, uint32_t xtal, uint32_t freq) {
    TC6800_tuner_cfg_cxd2856.tuner_dac = dac;
    priv.config.dac = dac;
    TC6800_tuner_cfg_cxd2856.tuner_dac_gain = dac_gain;
    priv.config.dac_gain = dac_gain;
    TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
    TC6800_tuner_cfg_cxd2856.tuner_crystal = xtal;
    priv.config.xtal = xtal;
    sprintf(msg, "dac: %d, dac_gain: %d, bw: %d, xtal: %d, freq: %d, 0x20: %02x\n",
            dac, dac_gain, bw, xtal, freq, i2c_reg[0x20]);
    _mt_fe_tn_set_DAC_tc6800_cxd2856(freq);
    m88tc6800_set_dac(&priv, freq, bw);
    finish();
}

int main() {
    suite_init();

    uint32_t dac_list[] = {4500, 4501, 4570, 7200};
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};
    uint32_t xtal_list[] = {24000, 27000};

    /* Phase A: fine frequency sweep. set_dac picks its ADC rate from the
     * frequency modulo a spur spacing, so this dimension has to stay dense. */
    for (int j = 0; j < sizeof(dac_list) / sizeof(dac_list[0]); j++) {
        for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
            for (uint32_t freq = freq_start; freq < freq_stop; freq += freq_stride) {
                for (int x = 0; x < sizeof(xtal_list) / sizeof(xtal_list[0]); x++) {
                    init();
                    i2c_reg_fill(freq % n_patterns);
                    run_case(dac_list[j], 2, bw_list[i], xtal_list[x], freq);
                }
            }
        }
    }

    /* Phase B: dac_gain feeds reg 0x22 as (0x40|0x80) + dac_gain*8 + 5, and
     * set_reg_bits(0x20, 3, 5, 6) makes reg 0x20's read-back an input.
     * Neither was swept at all before. */
    for (uint32_t dac_gain = 0; dac_gain < 256; dac_gain++) {
        for (uint32_t _20 = 0; _20 < 256; _20 += 17) {
            for (size_t p = 0; p < n_freq_probes; p++) {
                init();
                i2c_reg_fill(dac_gain % n_patterns);
                i2c_reg[0x20] = _20;
                run_case(4570, dac_gain, 8000, 27000, freq_probes[p]);
            }
        }
    }
    printf("set_dac OK\n");
}
