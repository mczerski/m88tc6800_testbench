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

void _mt_fe_tn_set_LO_tc6800_cxd2856(uint32_t freq_KHz,uint8_t mixer_sel)

{
  uint extraout_r0 = freq_KHz;
  uint8_t data;
  int extraout_r1 = mixer_sel;
  uint uVar1;
  uint8_t reg_data;
  bool bVar2;
  
                    /* Unresolved local var: uint32_t LDIV@[???]
                       Unresolved local var: uint8_t buf0@[???] */
  __gnu_mcount_nc();
  bVar2 = extraout_r0 == 499999;
  if (extraout_r0 < 500000) {
    bVar2 = extraout_r1 == 2;
  }
  if (bVar2) {
    if (extraout_r0 < 63000) {
      reg_data = 0x8b;
      TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x80;
      goto LAB_00089df4;
    }
    if (82999 < extraout_r0) {
      if (0x1e847 < extraout_r0) {
        if (extraout_r0 < 0x28c58) {
          reg_data = 0xd;
          TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x30;
          goto LAB_00089df4;
        }
        if (249999 < extraout_r0) {
          if (extraout_r0 < 0x51c98) {
            reg_data = 0xc;
            TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x18;
          }
          else {
            reg_data = 0x8;
            TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x10;
          }
          goto LAB_00089df4;
        }
LAB_00089fb0:
        reg_data = 0x9;
        TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x20;
        goto LAB_00089df4;
      }
LAB_00089f98:
      reg_data = 0xa;
      TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x40;
      goto LAB_00089df4;
    }
LAB_00089f8c:
    reg_data = 0x7a;
    TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x60;
  }
  else {
    if (extraout_r0 < 250000 || extraout_r1 != 3) {
      if (extraout_r0 < 56000) {
        reg_data = 0xb;
        TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x80;
        goto LAB_00089df4;
      }
      if (extraout_r0 < 83000) goto LAB_00089f8c;
      if (extraout_r0 < 0x1e848) goto LAB_00089f98;
      if (extraout_r0 < 0x28c58) {
        reg_data = 0x79;
        TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x30;
        goto LAB_00089df4;
      }
      if (extraout_r0 < 250000) goto LAB_00089fb0;
      if (extraout_r0 < 0x51c98) {
        reg_data = 0x78;
        TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x18;
        goto LAB_00089df4;
      }
      if (extraout_r0 < 500000) {
        reg_data = 0x8;
        TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x10;
        goto LAB_00089df4;
      }
      uVar1 = 0x2d77;
    }
    else {
      if (extraout_r0 < 0x514c8) {
        reg_data = 0xf8;
        TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x18;
        goto LAB_00089df4;
      }
      if (extraout_r0 < 500000) {
        reg_data = 0x88;
        TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0x10;
        goto LAB_00089df4;
      }
      uVar1 = 0x298f;
    }
    if ((uVar1 | 0xa0000) < extraout_r0) {
      reg_data = 0x4;
      TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 8;
    }
    else {
      reg_data = 0x74;
      TC6800_tuner_cfg_cxd2856.tuner_int_ldiv = 0xc;
    }
  }
LAB_00089df4:
  TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg = TC6800_tuner_cfg_cxd2856.tuner_int_ldiv * extraout_r0
  ;
  if (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg < 6700000) {
    data = 0x4;
  }
  else {
    data = 0x7;
  }
  _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x13,data,0x5,0x3);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x14,reg_data);
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

static void m88tc6800_set_lo(struct m88tc6800_priv *priv, u32 freq_khz, u8 mixer_type)
{
    u8 reg_data;
    if (freq_khz < 500000 && mixer_type == 2) {
        if (freq_khz < 63000) {
            reg_data = 0x8b;
            priv->ldiv = 0x80;
        }
        else if (freq_khz < 83000) {
            reg_data = 0x7a;
            priv->ldiv = 0x60;
        }
        else if (freq_khz < 125000) {
            reg_data = 0x0a;
            priv->ldiv = 0x40;
        }
        else if (freq_khz < 167000) {
            reg_data = 0x0d;
            priv->ldiv = 0x30;
        }
        else if (freq_khz < 250000) {
            reg_data = 0x09;
            priv->ldiv = 0x20;
        }
        else if (freq_khz < 335000) {
            reg_data = 0x0c;
            priv->ldiv = 0x18;
        }
        else {
            reg_data = 0x08;
            priv->ldiv = 0x10;
        }
    }
    else if (freq_khz < 250000 || mixer_type != 3) {
        if (freq_khz < 56000) {
            reg_data = 0x0b;
            priv->ldiv = 0x80;
        }
        else if (freq_khz < 83000) {
            reg_data = 0x7a;
            priv->ldiv = 0x60;
        }
        else if (freq_khz < 125000) {
            reg_data = 0x0a;
            priv->ldiv = 0x40;
        }
        else if (freq_khz < 167000) {
            reg_data = 0x79;
            priv->ldiv = 0x30;
        }
        else if (freq_khz < 25000) {
            reg_data = 0x09;
            priv->ldiv = 0x20;
        }
        else if (freq_khz < 335000) {
            reg_data = 0x78;
            priv->ldiv = 0x18;
        }
        else if (freq_khz < 500000) {
            reg_data = 0x08;
            priv->ldiv = 0x10;
        }
        else if (freq_khz < 667000) {
            reg_data = 0x74;
            priv->ldiv = 0x0c;
        }
        else {
            reg_data = 0x04;
            priv->ldiv = 0x08;
        }
    }
    else {
        if (freq_khz < 333000) {
            reg_data = 0xf8;
            priv->ldiv = 0x18;
        }
        else if (freq_khz < 500000) {
            reg_data = 0x88;
            priv->ldiv = 0x10;
        }
        else if (freq_khz < 666000) {
            reg_data = 0x74;
            priv->ldiv = 0x0c;
        }
        else {
            reg_data = 0x04;
            priv->ldiv = 0x08;
        }
    }
    priv->fvco_tg = freq_khz * priv->ldiv;
    if (priv->fvco_tg < 6700000) {
        m88tc6800_set_reg_bits(priv, 0x13, 4, 3, 5);
    }
    else {
        m88tc6800_set_reg_bits(priv, 0x13, 7, 3, 5);
    }
    m88tc6800_write_reg(priv, 0x14, reg_data);
}

int main() {
    for (uint32_t freq = 0; freq < 1000000; freq++) {
        init();
        printf("freq: %d\n", freq);
        _mt_fe_tn_set_LO_tc6800_cxd2856(freq, get_mixer_type_orig(freq));
        m88tc6800_set_lo(&priv, freq, m88tc6800_get_mixer_type(freq));
        finish();
        if (TC6800_tuner_cfg_cxd2856.tuner_int_ldiv != priv.ldiv) {
            printf("ldiv: actual %02x, expected %02x\n", priv.ldiv, TC6800_tuner_cfg_cxd2856.tuner_int_ldiv);
            return 0;
        }
        if (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg != priv.fvco_tg) {
            printf("fvco_tg: actual %02x, expected %02x\n", priv.fvco_tg, TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg);
            return 0;
        }
    }
}
