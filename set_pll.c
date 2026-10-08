#include "common.h"
#include "original.h"
#include "new.h"

static void run_case(uint32_t freq, uint8_t mixer_type, uint32_t xtal) {
    init();
    i2c_reg_fill(freq % n_patterns);
    TC6800_tuner_cfg_cxd2856.tuner_crystal = xtal;
    priv.config.xtal = xtal;
    sprintf(msg, "freq: %d, mixer_type: %d, xtal: %d\n", freq, mixer_type, xtal);
    _mt_fe_tn_set_LO_tc6800_cxd2856(freq, mixer_type);
    _mt_fe_tn_set_PLL_freq_tc6800_cxd2856();
    m88tc6800_set_lo(&priv, freq, mixer_type);
    m88tc6800_set_pll(&priv);
    finish();
}

int main() {
    suite_init();

    uint32_t start = freq_start < 1 ? 1 : freq_start;

    for (uint8_t mixer_type = 0; mixer_type < 4; mixer_type++) {
        for (uint32_t freq = start; freq < freq_stop; freq += freq_stride) {
            run_case(freq, mixer_type, 27000);
            run_case(freq, mixer_type, 24000);
        }
    }

    /* set_pll picks its reference divider from the crystal, and four of its
     * five paths are unreachable at 24/27 MHz:
     *   4500  -> crystal*2 == 9000     (/8 reference)
     *   13500 -> crystal*2 == 27000    (/8 reference)
     *   6750  -> crystal*2 == 0x34bc   (*4 / 0xd2f reference)
     *   16000 -> none of the above     (generic 2*crystal reference)
     * Nothing else in the driver supports these crystals, so they are
     * exercised here only, against the band edges rather than a full sweep. */
    uint32_t extra_xtal[] = {4500, 6750, 13500, 16000};
    for (uint8_t mixer_type = 0; mixer_type < 4; mixer_type++) {
        for (int x = 0; x < sizeof(extra_xtal) / sizeof(extra_xtal[0]); x++) {
            for (size_t p = 0; p < n_freq_probes; p++) {
                if (freq_probes[p] == 0)
                    continue;
                run_case(freq_probes[p], mixer_type, extra_xtal[x]);
            }
        }
    }
    printf("set_pll OK\n");
}
