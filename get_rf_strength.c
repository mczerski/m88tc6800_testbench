#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    uint8_t _8b_list[] = {0x55, 0x11, 0xbb, 0x99, 0xff};
    for (int i = 0; i < sizeof(_8b_list) / sizeof(_8b_list[0]); i++) {
        i2c_reg[0x8b] = _8b_list[i];
        for (uint32_t _63 = 0; _63 < 255; _63 += 10) {
            i2c_reg[0x63] = _63;
            for (uint32_t _8c = 0; _8c < 255; _8c += 10) {
                i2c_reg[0x8c] = _8c;
                for (uint32_t freq = 0; freq < 1000000; freq++) {
                    init();
                    TC6800_tuner_cfg_cxd2856.tuner_freq = freq;
                    priv.frequency_hz = freq * 1000;
                    //printf("freq: %d\n", freq);
                    int32_t rf_level;
                    TC6800_GetRFStrength(NULL, &rf_level);
                    s32 strength;
                    m88tc6800_get_rf_power(&priv, &strength);
                    //printf("freq: %d, rf: %d\n", freq, strength);
                    if (rf_level != strength) {
                        printf("rf level mismatch: %d - %d\n", rf_level, strength);
                        printf("freq: %d, 0x8b: %02X, 0x63: %02X, 0x8c: %02X\n", freq, _8b_list[i], _63, _8c);
                        return -1;
                    }
                    finish();
                }
            }
        }
    }
    printf("get_rf_strength OK\n");
}
