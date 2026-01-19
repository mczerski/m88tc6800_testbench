#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    TC6800_tuner_cfg_cxd2856.tuner_bandwidth = 8000;
    for (uint8_t mixer_type = 0; mixer_type < 4; mixer_type++) {
        for (uint32_t freq = 0; freq < 1000000; freq++) {
            init();
            //printf("freq: %d, mixer_type: %d\n", freq, mixer_type);
            _mt_fe_tn_set_tune_tc6800_cxd2856(freq, mixer_type, 0);
            m88tc6800_set_tune(&priv, freq, 8000, mixer_type, 0);
            finish();
        }
    }
    printf("set_tune OK\n");
}
