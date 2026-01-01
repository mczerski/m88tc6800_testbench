#include "common.h"

uint16_t get_mixer_type_orig(uint32_t freq_KHz_00) {
  uint16_t uVar9;
  unsigned uVar5;
  bool bVar11;
  bool bVar12;

  uVar9 = TC6800_tuner_cfg_cxd2856.tuner_mixer_type;
  if (((TC6800_tuner_cfg_cxd2856.tuner_mixer_type != 1) &&
      (TC6800_tuner_cfg_cxd2856.tuner_mixer_type != 2)) &&
     (TC6800_tuner_cfg_cxd2856.tuner_mixer_type != 3)) {
    if (freq_KHz_00 < 334001) {
      uVar9 = 2;
    }
    else if (TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp == 0x1) {
      if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x0) {
        uVar5 = freq_KHz_00 - 610000;
        bVar12 = 13999 < uVar5;
        bVar11 = uVar5 == 14000;
        if (14000 < uVar5) {
          bVar12 = 19999 < freq_KHz_00 - 800000;
          bVar11 = freq_KHz_00 - 800000 == 20000;
        }
        if ((bVar12 && !bVar11) && (12000 < freq_KHz_00 - 480000)) {
          uVar9 = 1;
          if (freq_KHz_00 - 366000 < 8001) {
            uVar9 = 3;
          }
          goto LAB_0008b808;
        }
      }
      uVar9 = 3;
    }
    else {
      uVar9 = 1;
    }
  }
LAB_0008b808:
  return uVar9;
}

int main() {

    for (uint32_t i = 0; i < 1000000; i++) {
        init();
        uint16_t expected = get_mixer_type_orig(i);
        uint16_t actual = m88tc6800_get_mixer_type(i);
        if (actual != expected) {
            printf("test freq: %d; actual %d different than expected %d\n", i, actual, expected);
            return 0;
        }
    }
}
