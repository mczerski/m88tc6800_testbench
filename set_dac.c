#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};
    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
        for (uint32_t freq = 0; freq < 1000000; freq++) {
            uint32_t bw = bw_list[i];
            init();
            TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
            priv.bandwidth_hz = bw;
            priv.config.xtal = 27000;
            //printf("freq: %d, bw: %d\n", freq, bw);
            _mt_fe_tn_set_DAC_tc6800_cxd2856(freq);
            m88tc6800_set_dac(&priv, freq);
            finish();
        }
    }
    //TODO: testy na tuner_dac, tuner_dac_gain, tuner crystal, tuner_bandwidth
    printf("set_dac OK\n");
}
