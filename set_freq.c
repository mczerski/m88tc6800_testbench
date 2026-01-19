#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};
    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
        uint32_t bw = bw_list[i];
        TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
        for (uint32_t freq = 1; freq < 1000000; freq++) {
            init();
            TC6800_tuner_cfg_cxd2856.tuner_crystal = 27000;
            priv.config.xtal = 27000;
            //printf("freq: %d, bw: %d, xtal: %d\n", freq, bw, priv.config.xtal);
            mt_fe_tn_set_freq_tc6800_cxd2856(freq);
            m88tc6800_set_freq(&priv, freq, bw);
            finish();
        }
    }
    //TODO: test with tuner_gpio_out: [0, 1]
    //get regs: 0x3e [0x1e, 0x80, 0], 0x7 [8, 0], 0x3c [0x80, 0]
    //tuner_mixer_type: [0, 1, 2, 3, 4]
    //tuner_harmonic_imp: [0, 1]
    //tuner_crystal: [24000, 27000]
    //tuner_int_lt: [0, 1, 2, 3]
    //tuner_mode: [0, 1, 2, 3]
    //tuner_custom_cfg: [0, 1]
    printf("set_freq OK\n");
}

