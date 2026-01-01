#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    for (uint8_t mixer_type = 0; mixer_type < 4; mixer_type++) {
        for (uint32_t freq = 0; freq < 1000000; freq++) {
            init();
            //printf("freq: %d, mixer_type: %d\n", freq, mixer_type);
            _mt_fe_tn_set_LO_tc6800_cxd2856(freq, mixer_type);
            m88tc6800_set_lo(&priv, freq, mixer_type);
            finish();
            if (TC6800_tuner_cfg_cxd2856.tuner_int_ldiv != priv.ldiv) {
                printf("ldiv: actual %02x, expected %02x\n", priv.ldiv, TC6800_tuner_cfg_cxd2856.tuner_int_ldiv);
                return 0;
            }
            if (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg != priv.fvco_tg) {
                printf("fvco_tg: actual %02x, expected %02x\n", priv.fvco_tg, TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg);
                return 0;
            }
        }
    }
    printf("set_mixer OK\n");
}
