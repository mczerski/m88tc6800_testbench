#include "common.h"
#include "original.h"
#include "new.h"

int main() {
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};
    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
        uint32_t bw = bw_list[i];
        TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
        uint8_t _3e_list[] = {0x1e, 0x80, 0};
        uint8_t _07_list[] = {8, 0, 1};
        uint8_t _3c_list[] = {0x80, 0};
        uint8_t _9a_list[] = {3, 4, 5, 9, 10, 11};
        for (int reg=0; reg < sizeof(_3e_list) * sizeof(_07_list) * sizeof(_3c_list) * sizeof(_9a_list); reg++) {
            int _3e_div = sizeof(_07_list) * sizeof(_3c_list) * sizeof(_9a_list);
            int _07_div = sizeof(_3c_list) * sizeof(_9a_list);
            int _3c_div = sizeof(_9a_list);
            i2c_reg[0x3e] = _3e_list[reg / _3e_div];
            i2c_reg[0x07] = _07_list[(reg % _3e_div) / _07_div];
            i2c_reg[0x3c] = _3c_list[((reg % _3e_div) % _07_div) / _3c_div];
            i2c_reg[0x9a] = _9a_list[((reg % _3e_div) % _07_div) % _3c_div];
            uint32_t xtal_list[] = {24000, 27000};
            for (int xtal=0; xtal < sizeof(xtal_list) / sizeof(xtal_list[0]); xtal++) {
                uint8_t harmonic_imp_list[] = {0, 1};
                for (int harmonic_imp=0; harmonic_imp < sizeof(harmonic_imp_list); harmonic_imp++) {
                    uint8_t int_lt_list[] = {0, 1, 2, 3};
                    for (int int_lt=0; int_lt < sizeof(int_lt_list); int_lt++) {
                        uint8_t mode_list[] = {0, 1};//, 1, 2, 3}; //TODO
                        for (int mode=0; mode < sizeof(mode_list); mode++) {
                            uint8_t custom_cfg_list[] = {0, 1};
                            for (int custom_cfg=0; custom_cfg<sizeof(custom_cfg_list); custom_cfg++) {
                                //printf("bw: %d, xtal: %d, harmonic_imp: %d, int_lt: %d, mode: %d, custom_cfg: %d, 0x3e: %d, 0x07: %d, 0x3c: %d, 0x9e: %d\n", bw, xtal, harmonic_imp, int_lt, mode, custom_cfg, i2c_reg[0x3e], i2c_reg[0x07], i2c_reg[0x3c], i2c_reg[0x9a]);
                                for (uint32_t freq = 1000; freq < 1000000; freq+=1000) {
                                    init();
                                    TC6800_tuner_cfg_cxd2856.tuner_crystal = xtal_list[xtal];
                                    priv.config.xtal = xtal_list[xtal];
                                    TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp = harmonic_imp_list[harmonic_imp];
                                    priv.config.harmonic_imp = harmonic_imp_list[harmonic_imp];;
                                    TC6800_tuner_cfg_cxd2856.tuner_int_lt = int_lt_list[int_lt];
                                    priv.config.int_lt = int_lt_list[int_lt];
                                    TC6800_tuner_cfg_cxd2856.tuner_mode = mode_list[mode];
                                    priv.config.mode = mode_list[mode];
                                    TC6800_tuner_cfg_cxd2856.tuner_custom_cfg = custom_cfg_list[custom_cfg];
                                    priv.config.custom_cfg = custom_cfg_list[custom_cfg];
                                    sprintf(msg, "freq: %d, bw: %d, xtal: %d, harmonic_imp: %d, int_lt: %d, mode: %d, custom_cfg: %d, 0x3e: %d, 0x07: %d, 0x3c: %d, 0x9e: %d\n", freq, bw, priv.config.xtal, priv.config.harmonic_imp, priv.config.int_lt, priv.config.mode, priv.config.custom_cfg, i2c_reg[0x3e], i2c_reg[0x07], i2c_reg[0x3c], i2c_reg[0x9a]);
                                    mt_fe_tn_set_freq_tc6800_cxd2856(freq);
                                    m88tc6800_set_freq(&priv, freq, bw);
                                    finish();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("set_freq OK\n");
}

