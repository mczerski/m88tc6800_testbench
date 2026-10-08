#include "common.h"
#include "original.h"
#include "new.h"

static int run_case(uint32_t freq) {
    int32_t rf_level;
    s32 strength;

    init();
    TC6800_tuner_cfg_cxd2856.tuner_freq = freq;
    priv.frequency_hz = freq * 1000;
    sprintf(msg, "freq: %d, 0x8b: %02x, 0x63: %02x, 0xc8: %02x\n",
            freq, i2c_reg[0x8b], i2c_reg[0x63], i2c_reg[0xc8]);
    TC6800_GetRFStrength(NULL, &rf_level);
    m88tc6800_get_rf_power(&priv, &strength);
    if (rf_level != strength) {
        printf("rf level mismatch: %d - %d\n", rf_level, strength);
        printf("%s", msg);
        return -1;
    }
    finish();
    return 0;
}

int main() {
    suite_init();

    uint8_t _8b_list[] = {0x55, 0x11, 0xbb, 0x99, 0xff, 0x00, 0x77, 0x44};

    /* Phase A: dense frequency sweep -- the band table in get_rf_power has
     * a dozen edges and each one shifts the result by a different offset. */
    for (int i = 0; i < sizeof(_8b_list); i++) {
        for (uint32_t _63 = 0; _63 < 256; _63 += 25) {
            for (uint32_t freq = freq_start; freq < freq_stop; freq += freq_stride) {
                i2c_reg_fill(freq % n_patterns);
                i2c_reg[0x8b] = _8b_list[i];
                i2c_reg[0x63] = _63;
                i2c_reg[0xc8] = (uint8_t)freq;
                if (run_case(freq))
                    return -1;
            }
        }
    }

    /* Phase B: every entry of xm_list_dBm. Index 0 is the only one the old
     * runner ever reached, and entries 0 and 1 are both 0x0 while the rest
     * climb to 0x12cd, so a wrong table would have gone unnoticed. */
    for (uint32_t _c8 = 0; _c8 < 256; _c8++) {
        for (int i = 0; i < sizeof(_8b_list); i++) {
            for (uint32_t _63 = 0; _63 < 256; _63 += 25) {
                for (size_t p = 0; p < n_freq_probes; p++) {
                    i2c_reg_fill(_c8 % n_patterns);
                    i2c_reg[0x8b] = _8b_list[i];
                    i2c_reg[0x63] = _63;
                    i2c_reg[0xc8] = _c8;
                    if (run_case(freq_probes[p]))
                        return -1;
                }
            }
        }
    }
    printf("get_rf_strength OK\n");
}
