#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    for (uint16_t mode = 0; mode < 4; mode++) {
        TC6800_tuner_cfg_cxd2856.tuner_mode = mode;
        priv.config.mode = mode;
        for (uint8_t im = 0; im < 4; im++) {
            TC6800_tuner_cfg_cxd2856.tuner_int_im = im;
            priv.config.im = im;
            for (uint8_t lt = 0; lt < 3; lt++) {
                TC6800_tuner_cfg_cxd2856.tuner_int_lt = lt;
                priv.config.lt = lt;
                for (uint8_t custom_cfg = 0; custom_cfg < 2; custom_cfg++) {
                    TC6800_tuner_cfg_cxd2856.tuner_custom_cfg = custom_cfg;
                    priv.config.custom_cfg = custom_cfg;
                    for (uint8_t harmonic_imp = 0; harmonic_imp < 2; harmonic_imp++) {
                        TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp = harmonic_imp;
                        priv.config.harmonic_imp = harmonic_imp;
                        //printf("mode: %d, im: %d, lt: %d, custom_cfg: %d, harmonic_imp: %d\n", mode, im, lt, custom_cfg, harmonic_imp);
                        for (uint32_t freq = 0; freq < 1000000; freq++) {
                            init();
                            //printf("mode: %d, im: %d, lt: %d, custom_cfg: %d, harmonic_imp: %d, freq: %d\n", mode, im, lt, custom_cfg, harmonic_imp, freq);
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
