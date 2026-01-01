#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    for (uint8_t mixer_type = 0; mixer_type < 4; mixer_type++) {
        for (uint32_t freq = 1; freq < 1000000; freq++) {
            init();
            TC6800_tuner_cfg_cxd2856.tuner_crystal = 27000;
            priv.config.xtal = 27000;
            //printf("freq: %d, crystal: %d, mixer_type: %d, xtal: 27k\n", freq, priv.config.xtal, mixer_type);
            _mt_fe_tn_set_LO_tc6800_cxd2856(freq, mixer_type);
            _mt_fe_tn_set_PLL_freq_tc6800_cxd2856();
            m88tc6800_set_lo(&priv, freq, mixer_type);
            m88tc6800_set_pll(&priv);
            finish();

            init();
            TC6800_tuner_cfg_cxd2856.tuner_crystal = 24000;
            priv.config.xtal = 24000;
            //printf("freq: %d, crystal: %d, mixer_type: %d, xtal: 24k\n", freq, priv.config.xtal, mixer_type);
            _mt_fe_tn_set_LO_tc6800_cxd2856(freq, mixer_type);
            _mt_fe_tn_set_PLL_freq_tc6800_cxd2856();
            m88tc6800_set_lo(&priv, freq, mixer_type);
            m88tc6800_set_pll(&priv);
            finish();
        }
    }
    printf("set_pll OK\n");
}
