#include "common.h"
#include "original.h"
#include "m88tc6800.h"

int main() {
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};
    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
        uint32_t bw = bw_list[i];
        init();
        TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
        priv.bandwidth_hz = bw;
        //printf("bw: %d\n", bw);
        _mt_fe_tn_set_BB_tc6800_cxd2856();
        m88tc6800_set_bandwidth(&priv);
        finish();
    }
    printf("set_bandwidth OK\n");
}
