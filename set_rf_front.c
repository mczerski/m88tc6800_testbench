#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    TC6800_tuner_cfg_cxd2856.tuner_mode = 0;
    TC6800_tuner_cfg_cxd2856.tuner_int_lt = 2;
    TC6800_tuner_cfg_cxd2856.tuner_int_im = 2;
    TC6800_tuner_cfg_cxd2856.tuner_custom_cfg = 0;
    TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp = 1;

    for (uint32_t freq = 0; freq < 1000000; freq++) {
        init();
        //printf("freq: %d\n", freq);
        _mt_fe_tn_set_RF_front_tc6800_cxd2856(freq);
        m88tc6800_set_rf_frontend(&priv, freq);
        finish();
    }
    printf("set_rf_front OK\n");
}
