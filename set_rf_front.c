#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    for (uint32_t freq = 0; freq < 1000000; freq++) {
        init();
        //printf("freq: %d\n", freq);
        _mt_fe_tn_set_RF_front_tc6800_cxd2856(freq);
        m88tc6800_set_rf_frontend(&priv, freq);
        finish();
    }
    //TODO: test with tuner_int_im [0, 1, 2, 3]
    //.tuner_int_lt [0, 1, 2]
    //tuner_custom_cfg [0, 1]
    //.tuner_harmonic_imp [0, 1]
    printf("set_rf_front OK\n");
}
