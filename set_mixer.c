#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    for (uint8_t mixer_type = 0; mixer_type < 4; mixer_type++) {
        for (uint32_t freq = 0; freq < 1000000; freq++) {
            init();
            //printf("freq: %d, mixer_type %d\n", freq, mixer_type);
            _mt_fe_tn_set_Mixer_tc6800_cxd2856(freq, mixer_type);
            m88tc6800_set_mixer(&priv, freq, mixer_type);
            finish();
        }
    }
    printf("set_mixer OK\n");
}
