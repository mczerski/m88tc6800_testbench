#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    suite_init();

    /* mixer_type reaches this function as 1, 2 or 3 from get_mixer_type and
     * as a hardcoded 1 from set_tune, but the parameter is a u8 and the
     * "anything that is not 2 or 3 means 1" fold is worth pinning down. */
    uint8_t mixer_list[] = {0, 1, 2, 3, 4, 0x32, 0xc8, 0xff};
    size_t n_mixer = sizeof(mixer_list) / sizeof(mixer_list[0]);

    for (int m = 0; m < n_mixer; m++) {
        for (uint32_t freq = freq_start; freq < freq_stop; freq += freq_stride) {
            init();
            i2c_reg_fill(freq % n_patterns);
            sprintf(msg, "mixer_type: %d, freq: %d, 0x0b: %02x\n",
                    mixer_list[m], freq, i2c_reg[0x0b]);
            _mt_fe_tn_set_Mixer_tc6800_cxd2856(freq, mixer_list[m]);
            m88tc6800_set_mixer(&priv, freq, mixer_list[m]);
            finish();
        }
    }

    for (int m = 0; m < n_mixer; m++) {
        for (uint32_t _0b = 0; _0b < 256; _0b++) {
            for (size_t p = 0; p < n_freq_probes; p++) {
                uint32_t freq = freq_probes[p];
                init();
                i2c_reg_fill(_0b % n_patterns);
                i2c_reg[0x0b] = _0b;
                sprintf(msg, "mixer_type: %d, freq: %d, 0x0b: %02x\n",
                        mixer_list[m], freq, i2c_reg[0x0b]);
                _mt_fe_tn_set_Mixer_tc6800_cxd2856(freq, mixer_list[m]);
                m88tc6800_set_mixer(&priv, freq, mixer_list[m]);
                finish();
            }
        }
    }
    printf("set_mixer OK\n");
}
