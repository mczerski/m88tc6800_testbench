#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    for (uint32_t freq = 0; freq < 1000000; freq++) {
        init();
        TC6800_tuner_cfg_cxd2856.tuner_crystal = 27000;
        priv.config.xtal = 27000;
        //printf("freq: %d, crystal: %d\n", freq, priv.config.xtal);
        _mt_fe_tn_preset_tc6800_cxd2856();
        m88tc6800_preset(&priv);
        finish();

        init();
        TC6800_tuner_cfg_cxd2856.tuner_crystal = 24000;
        priv.config.xtal = 24000;
        //printf("freq: %d, crystal: %d\n", freq, priv.config.xtal);
        _mt_fe_tn_preset_tc6800_cxd2856();
        m88tc6800_preset(&priv);
        finish();
    }
    printf("preset OK\n");
}
