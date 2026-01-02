#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    for (uint32_t freq = 0; freq < 1000000; freq++) {
        init();
        TC6800_tuner_cfg_cxd2856.tuner_freq = freq;
        priv.frequency_hz = freq * 1000;
        //printf("freq: %d\n", freq);
        int32_t rf_level;
        TC6800_GetRFStrength(NULL, &rf_level);
        u16 tmp;
        s32 strength;
        m88tc6800_get_rf_strength(&priv, &tmp);
        strength = (int16_t)tmp;
        printf("freq: %d, rf: %d\n", freq, strength);
        if (rf_level != strength) {
            printf("rf level mismatch: %d - %d\n", rf_level, strength);
            return -1;
        }
        finish();
    }
    printf("get_rf_strength OK\n");
}
