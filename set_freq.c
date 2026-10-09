#include "common.h"
#include "original.h"
#include "new.h"

static void set_xtal(uint32_t xtal) {
    TC6800_tuner_cfg_cxd2856.tuner_crystal = xtal;
    priv.config.xtal = xtal;
}

static void set_xtal_cap(uint8_t cap) {
    TC6800_tuner_cfg_cxd2856.tuner_crystal_cap = cap;
    priv.config.xtal_cap = cap;
}

static void run_case(uint32_t freq, uint32_t bw) {
    TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
    sprintf(msg, "freq: %d, bw: %d, xtal: %d, xtal_cap: %02x, "
                 "0x3e: %02x, 0x07: %02x, 0x3c: %02x, 0x9a: %02x, "
                 "0x4a: %02x, 0x4b: %02x, 0x4c: %02x, 0x50: %02x, 0x54: %02x\n",
            freq, bw, priv.config.xtal, priv.config.xtal_cap,
            i2c_reg[0x3e], i2c_reg[0x07], i2c_reg[0x3c], i2c_reg[0x9a],
            i2c_reg[0x4a], i2c_reg[0x4b], i2c_reg[0x4c], i2c_reg[0x50], i2c_reg[0x54]);
    mt_fe_tn_set_freq_tc6800_cxd2856(freq);
    m88tc6800_set_freq(&priv, freq, bw);
    finish();
}

int main() {
    suite_init();

    /* set_freq is by far the heaviest entry point (it pulls in preset,
     * set_rf_frontend, set_mixer, set_lo, set_pll, set_bandwidth and
     * set_dac), so its default frequency stride is 1000 rather than 1.
     * FREQ_STRIDE still overrides it. */
    uint32_t stride = freq_stride > 1 ? freq_stride : 1000;
    uint32_t start = freq_start < 1000 ? 1000 : freq_start;

    /* Registers set_freq itself branches on.
     *   0x3e bits 1..4 decide whether the tuner is reset first
     *   0x07 bit 3 picks between two 0x07/0x11 write sequences
     *   0x9a is read by preset and masked with 0xf, so values above 0x0f
     *        are what actually exercises the mask */
    uint8_t _3e_list[] = {0x1e, 0x80, 0x02, 0x00};
    uint8_t _07_list[] = {0x08, 0x00};
    uint8_t _9a_list[] = {0x03, 0x0b, 0x1f, 0x45, 0xf0, 0xff};
    uint32_t xtal_list[] = {24000, 27000};
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};

    /* Phase A: the register cross product against a dense frequency sweep. */
    printf("phase A: 0x3e/0x07/0x9a register cross product\n");
    for (int a = 0; a < sizeof(_3e_list); a++) {
      for (int b = 0; b < sizeof(_07_list); b++) {
        for (int d = 0; d < sizeof(_9a_list); d++) {
          for (int x = 0; x < sizeof(xtal_list) / sizeof(xtal_list[0]); x++) {
            for (uint32_t freq = start; freq < freq_stop; freq += stride) {
              init();
              i2c_reg_fill(freq % n_patterns);
              i2c_reg[0x3e] = _3e_list[a];
              i2c_reg[0x07] = _07_list[b];
              i2c_reg[0x3c] = 0x80;
              i2c_reg[0x9a] = _9a_list[d];
              set_xtal(xtal_list[x]);
              set_xtal_cap(0x18);
              run_case(freq, 8000);
            }
          }
        }
      }
    }

    /* Phase B: bandwidth, against the band edges. */
    printf("phase B: bandwidth\n");
    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
      for (unsigned pattern = 0; pattern < n_patterns; pattern++) {
        for (int x = 0; x < sizeof(xtal_list) / sizeof(xtal_list[0]); x++) {
          for (size_t p = 0; p < n_freq_probes; p++) {
            if (freq_probes[p] < 1000)
              continue;
            init();
            i2c_reg_fill(pattern);
            i2c_reg[0x3c] = 0x80;
            set_xtal(xtal_list[x]);
            set_xtal_cap(0x18);
            run_case(freq_probes[p], bw_list[i]);
          }
        }
      }
    }

    /* Phase C: the tuned-frequency sanity check at the tail of set_freq
     * reads 0x4a/0x4b/0x4c and shifts by bits 5..6 of 0x4c. With all three
     * reading 0 the shift amount was always 0 and the computed frequency
     * always 0, so neither the shift nor the comparison was exercised. */
    printf("phase C: 0x4a/0x4b/0x4c frequency check\n");
    uint8_t _4a_list[] = {0x00, 0x0f, 0x5a, 0xff};
    uint8_t _4b_list[] = {0x00, 0x7f, 0xff};
    uint8_t _4c_list[] = {0x00, 0x20, 0x40, 0x60, 0xff};
    for (int a = 0; a < sizeof(_4a_list); a++) {
      for (int b = 0; b < sizeof(_4b_list); b++) {
        for (int c = 0; c < sizeof(_4c_list); c++) {
          for (int x = 0; x < sizeof(xtal_list) / sizeof(xtal_list[0]); x++) {
            for (size_t p = 0; p < n_freq_probes; p++) {
              if (freq_probes[p] < 1000)
                continue;
              init();
              i2c_reg_fill(p % n_patterns);
              i2c_reg[0x3c] = 0x80;
              i2c_reg[0x4a] = _4a_list[a];
              i2c_reg[0x4b] = _4b_list[b];
              i2c_reg[0x4c] = _4c_list[c];
              set_xtal(xtal_list[x]);
              set_xtal_cap(0x18);
              run_case(freq_probes[p], 8000);
            }
          }
        }
      }
    }
    printf("set_freq OK\n");
}
