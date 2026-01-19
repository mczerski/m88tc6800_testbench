#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    for (uint16_t mode = 0; mode < 4; mode++) {
        TC6800_tuner_cfg_cxd2856.tuner_mode = mode;
        priv.config.mode = mode;
        for (uint8_t int_im = 0; int_im < 4; int_im++) {
            TC6800_tuner_cfg_cxd2856.tuner_int_im = int_im;
            priv.config.int_im = int_im;
            for (uint8_t int_lt = 0; int_lt < 3; int_lt++) {
                TC6800_tuner_cfg_cxd2856.tuner_int_lt = int_lt;
                priv.config.int_lt = int_lt;
                for (uint8_t custom_cfg = 0; custom_cfg < 2; custom_cfg++) {
                    TC6800_tuner_cfg_cxd2856.tuner_custom_cfg = custom_cfg;
                    priv.config.custom_cfg = custom_cfg;
                    for (uint8_t harmonic_imp = 0; harmonic_imp < 2; harmonic_imp++) {
                        TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp = harmonic_imp;
                        priv.config.harmonic_imp = harmonic_imp;
                        //printf("mode: %d, int_im: %d, int_lt: %d, custom_cfg: %d, harmonic_imp: %d\n", mode, int_im, int_lt, custom_cfg, harmonic_imp);
                        for (uint32_t freq = 0; freq < 1000000; freq++) {
                            init();
                            //printf("mode: %d, int_im: %d, int_lt: %d, custom_cfg: %d, harmonic_imp: %d, freq: %d\n", mode, int_im, int_lt, custom_cfg, harmonic_imp, freq);
                            _mt_fe_tn_set_RF_front_tc6800_cxd2856(freq);
                            m88tc6800_set_rf_frontend(&priv, freq);
                            finish();
                        }
                    }
                }
            }
        }
    }
    printf("set_rf_front OK\n");
}
