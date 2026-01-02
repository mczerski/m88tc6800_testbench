#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    TC6800_tuner_cfg_cxd2856.tuner_bandwidth = 8000;
    for (uint32_t freq = 1; freq < 1000000; freq++) {
        init();
        TC6800_tuner_cfg_cxd2856.tuner_crystal = 27000;
        priv.config.xtal = 27000;
        //printf("freq: %d, crystal: %d, mixer_type: %d\n", freq, priv.config.xtal, mixer_type);
        mt_fe_tn_set_freq_tc6800_cxd2856(freq);
        m88tc6800_set_freq(&priv, freq, 8000);
        finish();
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

