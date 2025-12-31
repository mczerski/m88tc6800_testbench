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

void _mt_fe_tn_set_Mixer_tc6800_cxd2856(uint32_t freq_KHz,uint8_t mixer_sel)

{
  uint extraout_r0 = freq_KHz;
  uint8_t uVar1;
  int extraout_r1 = mixer_sel;
  int iVar2;
  
                    /* Unresolved local var: uint8_t buf0@[DW_OP_reg5(r5)] */
  __gnu_mcount_nc();
  iVar2 = extraout_r1;
  if (extraout_r1 == 2) {
    if (124999 < extraout_r0) {
      if (extraout_r0 < 167000) {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x2f,0x10);
      }
      else if (extraout_r0 < 250000) {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x2f,0x21);
      }
      else {
        if (extraout_r0 < 335000) {
          uVar1 = 0x32;
        }
        else {
          uVar1 = 0x43;
        }
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x2f,uVar1);
      }
      goto LAB_00089d0c;
    }
  }
  else if (extraout_r1 != 3) {
    iVar2 = 1;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x2f,0x0);
LAB_00089d0c:
  _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0xb,(uint8_t)iVar2,0x1,0x0);
  if (extraout_r0 - 330000 < 70001) {
    uVar1 = 0x4;
  }
  else {
    uVar1 = 0x0;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x32,uVar1);
  return;
}

static u8 m88tc6800_get_mixer_type(u32 freq_khz)
{
    if (freq_khz <= 334000) {
        return 2;
    }
    if ((freq_khz >= 480000 && freq_khz <= 492000) ||
           (freq_khz >= 610000 && freq_khz <= 624000) ||
           (freq_khz >= 800000 && freq_khz <= 820000) ||
           (freq_khz >= 366000 && freq_khz <= 374000)) {
        return 3;
    }
    return 1;
}

static void m88tc6800_set_mixer(struct m88tc6800_priv *priv, u32 freq_khz, u8 mixer_type)
{
    u8 tmp = mixer_type;
    if (mixer_type == 2) {
        if (freq_khz >= 125000) {
            if (freq_khz < 167000) {
                m88tc6800_write_reg(priv, 0x2f, 0x10);
            }
            else if (freq_khz < 250000) {
                m88tc6800_write_reg(priv, 0x2f, 0x21);
            }
            else if (freq_khz < 335000) {
                m88tc6800_write_reg(priv, 0x2f, 0x32);
            }
            else {
                m88tc6800_write_reg(priv, 0x2f, 0x43);
            }
        }
        else {
            m88tc6800_write_reg(priv, 0x2f, 0x00);
        }
    }
    else {
        if (mixer_type != 3) {
            tmp = 1;
        }
        m88tc6800_write_reg(priv, 0x2f, 0x00);
    }
    m88tc6800_set_reg_bits(priv, 0x0b, tmp, 0, 1);
    if (freq_khz >= 330000 && freq_khz <= 400000) {
        m88tc6800_write_reg(priv, 0x32, 0x04);
    }
    else {
        m88tc6800_write_reg(priv, 0x32, 0x00);
    }
}

int main() {
    for (uint32_t freq = 0; freq < 1000000; freq++) {
        init();
        printf("freq: %d\n", freq);
        _mt_fe_tn_set_Mixer_tc6800_cxd2856(freq, get_mixer_type_orig(freq));
        m88tc6800_set_mixer(&priv, freq, m88tc6800_get_mixer_type(freq));
        finish();
    }
}
