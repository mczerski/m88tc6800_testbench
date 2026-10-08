#include "common.h"
#include "original.h"
#include "new.h"

static int check_derived(uint32_t freq, uint8_t mixer_type) {
    if (TC6800_tuner_cfg_cxd2856.tuner_int_ldiv != priv.lo_div) {
        printf("lo_div: actual %02x, expected %02x\n", priv.lo_div, TC6800_tuner_cfg_cxd2856.tuner_int_ldiv);
        printf("%s", msg);
        return -1;
    }
    if (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg != priv.fvco_target) {
        printf("fvco_target: actual %02x, expected %02x\n", priv.fvco_target, TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg);
        printf("%s", msg);
        return -1;
    }
    return 0;
}

int main() {
    suite_init();

    for (uint8_t mixer_type = 0; mixer_type < 4; mixer_type++) {
        for (uint32_t freq = freq_start; freq < freq_stop; freq += freq_stride) {
            init();
            i2c_reg_fill(freq % n_patterns);
            sprintf(msg, "freq: %d, mixer_type: %d, 0x13: %02x\n", freq, mixer_type, i2c_reg[0x13]);
            _mt_fe_tn_set_LO_tc6800_cxd2856(freq, mixer_type);
            m88tc6800_set_lo(&priv, freq, mixer_type);
            finish();
            if (check_derived(freq, mixer_type))
                return -1;
        }
    }

    for (uint8_t mixer_type = 0; mixer_type < 4; mixer_type++) {
        for (uint32_t _13 = 0; _13 < 256; _13++) {
            for (size_t p = 0; p < n_freq_probes; p++) {
                uint32_t freq = freq_probes[p];
                init();
                i2c_reg_fill(_13 % n_patterns);
                i2c_reg[0x13] = _13;
                sprintf(msg, "freq: %d, mixer_type: %d, 0x13: %02x\n", freq, mixer_type, i2c_reg[0x13]);
                _mt_fe_tn_set_LO_tc6800_cxd2856(freq, mixer_type);
                m88tc6800_set_lo(&priv, freq, mixer_type);
                finish();
                if (check_derived(freq, mixer_type))
                    return -1;
            }
        }
    }
    printf("set_lo OK\n");
}
