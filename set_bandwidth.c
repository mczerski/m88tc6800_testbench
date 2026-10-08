#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    suite_init();

    uint32_t bw_list[] = {
        0, 1,
        1699, 1700, 1701,
        5000,
        5999, 6000, 6001,
        6999, 7000, 7001,
        7999, 8000, 8001,
        10000,
        0xffffffff,
    };

    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
        for (unsigned pattern = 0; pattern < n_patterns; pattern++) {
            uint32_t bw = bw_list[i];
            init();
            i2c_reg_fill(pattern);
            TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
            sprintf(msg, "bw: %u, pattern: %u\n", bw, pattern);
            _mt_fe_tn_set_BB_tc6800_cxd2856();
            m88tc6800_set_bandwidth(&priv, bw);
            finish();
        }
    }
    printf("set_bandwidth OK\n");
}
