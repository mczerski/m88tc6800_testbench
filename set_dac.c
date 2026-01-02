#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    uint32_t dac_list[] = {4500, 4501, 4570, 7200};
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};
    for (int j = 0; j < sizeof(dac_list) / sizeof(dac_list[0]); j++) {
        TC6800_tuner_cfg_cxd2856.tuner_dac = dac_list[j];
        priv.config.dac = dac_list[j];
        for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
            TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw_list[i];
            for (uint32_t freq = 0; freq < 1000000; freq++) {
                init();
                TC6800_tuner_cfg_cxd2856.tuner_crystal = 24000;
                priv.config.xtal = 24000;
                //printf("dac: %d, freq: %d, bw: %d, xtal: 24k\n", dac_list[j], freq, bw_list[i]);
                _mt_fe_tn_set_DAC_tc6800_cxd2856(freq);
                m88tc6800_set_dac(&priv, freq, bw_list[i]);
                finish();

                init();
                TC6800_tuner_cfg_cxd2856.tuner_crystal = 27000;
                priv.config.xtal = 27000;
                //printf("dac: %d, freq: %d, bw: %d, xtal: 27k\n", dac_list[j], freq, bw_list[i]);
                _mt_fe_tn_set_DAC_tc6800_cxd2856(freq);
                m88tc6800_set_dac(&priv, freq, bw_list[i]);
                finish();
            }
        }
    }
    printf("set_dac OK\n");
}
