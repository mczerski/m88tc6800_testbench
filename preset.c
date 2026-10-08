#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    suite_init();

    TC6800_tuner_cfg_cxd2856.tuner_mode = 0;

    uint32_t xtal_list[] = {24000, 27000};

    for (unsigned pattern = 0; pattern < n_patterns; pattern++) {
        for (uint32_t _9a = 0; _9a < 256; _9a++) {
            for (int x = 0; x < sizeof(xtal_list) / sizeof(xtal_list[0]); x++) {
                init();
                i2c_reg_fill(pattern);
                i2c_reg[0x9a] = _9a;
                TC6800_tuner_cfg_cxd2856.tuner_crystal = xtal_list[x];
                priv.config.xtal = xtal_list[x];
                sprintf(msg, "pattern: %u, xtal: %d, 0x9a: %02x\n",
                        pattern, priv.config.xtal, i2c_reg[0x9a]);
                _mt_fe_tn_preset_tc6800_cxd2856();
                m88tc6800_preset(&priv);
                finish();
            }
        }
    }
    printf("preset OK\n");
}
