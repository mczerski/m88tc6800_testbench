#include "common.h"
#include "original.h"
#include "new.h"

static void run_case(uint32_t freq, uint32_t bw) {
    TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
    sprintf(msg, "freq: %d, bw: %d, 0x9a: %02x, 0x0b: %02x, 0x13: %02x, 0x20: %02x\n",
            freq, bw, i2c_reg[0x9a], i2c_reg[0x0b], i2c_reg[0x13], i2c_reg[0x20]);
    _mt_fe_tn_set_tune_tc6800_cxd2856(freq, 1, 0);
    m88tc6800_set_tune(&priv, freq, bw, 1, 0);
    finish();
}

int main() {
    suite_init();

    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};

    for (uint32_t freq = freq_start; freq < freq_stop; freq += freq_stride) {
        init();
        i2c_reg_fill(freq % n_patterns);
        run_case(freq, 8000);
    }

    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
        for (unsigned pattern = 0; pattern < n_patterns; pattern++) {
            for (size_t p = 0; p < n_freq_probes; p++) {
                init();
                i2c_reg_fill(pattern);
                run_case(freq_probes[p], bw_list[i]);
            }
        }
    }
    printf("set_tune OK\n");
}
