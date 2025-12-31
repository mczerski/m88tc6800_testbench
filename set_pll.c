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

void _mt_fe_tn_set_PLL_freq_tc6800_cxd2856(void)

{
  uint uVar1;
  byte bVar2;
  uint32_t uVar3;
  uint32_t uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint8_t uVar8;
  int extraout_r1;
  int extraout_r1_00;
  char cVar9;
  int iVar10;
  byte bVar11;
  uint uVar12;
  uint uVar13;
  uint8_t reg_data;
  uint uVar14;
  uint uVar15;
  bool bVar16;
  uint uVar17;
  byte local_38;
  
                    /* Unresolved local var: uint32_t LDIV@[???]
                       Unresolved local var: uint32_t Fvco_KHz@[???]
                       Unresolved local var: uint32_t Fvco_in_KHz@[???]
                       Unresolved local var: uint32_t pll_ref@[???]
                       Unresolved local var: uint8_t pll_fdiv_bit_sel@[???]
                       Unresolved local var: uint32_t buf32@[???]
                       Unresolved local var: uint32_t NS4@[???]
                       Unresolved local var: uint32_t fin@[???]
                       Unresolved local var: uint8_t pll_sdm_en@[???]
                       Unresolved local var: uint8_t spur_opti_by_dsm@[???]
                       Unresolved local var: uint32_t FDIV_F@[???]
                       Unresolved local var: uint32_t FDIV_N@[???]
                       Unresolved local var: uint32_t FDIV_FIN@[???]
                       Unresolved local var: uint8_t ICP_CODE@[???]
                       Unresolved local var: uint8_t kvco_tune@[???]
                       Unresolved local var: uint8_t buf@[???]
                       Unresolved local var: uint32_t freq_LO_KHz@[???]
                       Unresolved local var: uint32_t harmK@[???]
                       Unresolved local var: uint8_t Icp_scale_en@[???] */
  __gnu_mcount_nc();
  uVar4 = TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg;
  uVar3 = TC6800_tuner_cfg_cxd2856.tuner_crystal;
  uVar1 = TC6800_tuner_cfg_cxd2856.tuner_crystal >> 1;
  uVar12 = TC6800_tuner_cfg_cxd2856.tuner_crystal * 2;
  if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 24000) {
    iVar10 = __aeabi_uidiv(TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg,
                           TC6800_tuner_cfg_cxd2856.tuner_int_ldiv);
    if (0x176e < iVar10 - 0x518b1U) {
      cVar9 = '\0';
      uVar13 = 48000;
      goto LAB_00089804;
    }
    uVar6 = 0x5dc;
    cVar9 = '\0';
    uVar13 = 24000;
LAB_00089808:
    uVar5 = __aeabi_uidiv(uVar4,uVar6);
    extraout_r1_00 = __aeabi_uidivmod(uVar4,uVar6);
    uVar6 = __aeabi_uidiv(extraout_r1_00 << 0xc,uVar6);
  }
  else {
    if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 27000) {
      iVar10 = (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg / 27000 -
               (((int)((ulonglong)(TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg >> 2) * 0x4dac1b9d >>
                      0x20) << 0x15) >> 0x1f)) * 27000;
      if (((iVar10 + 10U < TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg) &&
          (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg < iVar10 + 0x3f2U)) ||
         ((TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg < iVar10 - 10U &&
          (iVar10 - 0x3f2U < TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg)))) {
        cVar9 = '\x02';
        uVar13 = 18000;
      }
      else if ((iVar10 + 0x3fcU < TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg) &&
              (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg < iVar10 + 0x7e4U)) {
        cVar9 = '\x01';
        uVar13 = 18000;
      }
      else if (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg < iVar10 - 0x3fcU) {
        cVar9 = iVar10 - 0x7e4U < TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg;
        uVar13 = 18000;
        if (!(bool)cVar9) {
          uVar13 = 54000;
        }
      }
      else {
        cVar9 = '\0';
        uVar13 = 54000;
      }
LAB_00089804:
      uVar6 = uVar13 >> 4;
      goto LAB_00089808;
    }
    uVar13 = uVar12;
    if (uVar12 == 9000 || uVar12 == 27000) {
      uVar6 = uVar12 >> 3;
      iVar10 = TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg << 1;
      uVar5 = __aeabi_uidiv(iVar10,uVar6);
      extraout_r1 = __aeabi_uidivmod(iVar10,uVar6);
      cVar9 = '\0';
      uVar6 = __aeabi_uidiv(extraout_r1 << 0xc,uVar6);
    }
    else {
      cVar9 = '\0';
      if (uVar12 != 0x34bc) goto LAB_00089804;
      uVar5 = (TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg * 4) / 0xd2f;
      uVar6 = (((TC6800_tuner_cfg_cxd2856.tuner_int_fvco_tg * 4) % 0xd2f) * 0x1000) / 0xd2f;
    }
  }
  uVar15 = (uVar5 << 0x12) >> 0x16;
  uVar14 = uVar5 & 0xf;
  if ((uVar6 & 0xfff) - 0x21 < 0xfbf) {
    reg_data = (uint8_t)uVar6;
    bVar16 = true;
    local_38 = (byte)((uVar6 << 0x14) >> 0x1c) | 0x30;
    uVar6 = uVar13 * (uVar6 & 0xfff) >> 0x10;
  }
  else {
    if ((uVar6 & 0x800) != 0) {
      uVar15 = (uVar5 + 1) * 0x40000 >> 0x16;
      uVar14 = uVar5 + 1 & 0xf;
    }
    bVar16 = false;
    reg_data = 0x0;
    local_38 = 0x30;
    uVar6 = 0;
  }
  uVar6 = uVar13 * uVar15 + uVar6 + (uVar13 * uVar14 >> 4);
  if (uVar6 < 8000000) {
    uVar6 = (uVar6 * -4 + 32000000) / 0x9eb1;
  }
  else {
    uVar6 = -(((uVar6 + 0x3f85ee00) * 4) / 0x9eb1);
  }
  uVar7 = uVar6 + 0x100;
  uVar17 = uVar7 * 0x80000 >> 0x18;
  uVar5 = (uVar17 & 1) + (uVar7 >> 6) & 0xff;
  if (uVar3 == uVar13) {
    uVar17 = uVar17 - ((int)(uVar6 << 0x1b) >> 0x1f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x11);
    uVar8 = 0x11;
LAB_000898b0:
    uVar5 = uVar17 & 0xff;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,uVar8);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x10);
    uVar8 = 0x8;
  }
  else {
    if (uVar13 == uVar12 / 3) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x11);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x33);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x10);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xb);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x15);
      uVar5 = uVar5 + (uVar17 - ((int)(uVar6 << 0x1b) >> 0x1f)) & 0xff;
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x43);
      goto LAB_00089584;
    }
    if (uVar13 == uVar3 / 3) {
      uVar12 = uVar7 * 0x100000 >> 0x18;
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x11);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x33);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x10);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x15);
      uVar5 = ((uVar17 + uVar12) - ((int)(uVar6 << 0x1c) >> 0x1f)) + (uVar12 & 1) & 0xff;
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x63);
      goto LAB_00089584;
    }
    if (uVar1 == uVar13) {
      uVar17 = (uVar7 >> 4) - ((int)(uVar6 << 0x1c) >> 0x1f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x11);
      uVar8 = 0x22;
      goto LAB_000898b0;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x11);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x11);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x10);
    uVar8 = 0xb;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,uVar8);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x15);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x13);
LAB_00089584:
  if (bVar16) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x12);
    uVar5 = uVar5 - 1 & 0xff;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x21);
  }
  else {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x12);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x0);
  }
  if (cVar9 == '\x01') {
    uVar5 = uVar5 >> 1;
  }
  else if (cVar9 == '\x02') {
    uVar5 = uVar5 >> 2;
  }
  if (uVar5 < 2) {
    uVar5 = 2;
  }
  bVar11 = (byte)uVar5;
  if (0xe < uVar5) {
    bVar11 = 0xf;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0xa);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x63);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0xf);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x3d);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0xb);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xa1);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x3d,0xff);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x1c);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x7e);
  bVar2 = (byte)(uVar14 << 3);
  if (bVar16) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x19);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,bVar2 | 3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x19);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,bVar2 | 7);
  }
  else {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x19);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,bVar2 | 2);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x19);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,bVar2 | 6);
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x17);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,(byte)(uVar15 >> 8) | 0xc);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x18);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,(uint8_t)uVar15);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x1a);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,local_38);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x1b);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,reg_data);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0xe);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x58);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x14);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x4c);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x13);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,bVar11 | 0x10);
  return;
}

void m88tc6800_set_pll(struct m88tc6800_priv *priv)
{
  uint uVar1;
  byte bVar2;
  uint32_t uVar3;
  uint32_t uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint8_t uVar8;
  int extraout_r1;
  int extraout_r1_00;
  char cVar9;
  int iVar10;
  byte bVar11;
  uint uVar12;
  uint uVar13;
  uint8_t reg_data;
  uint uVar14;
  uint uVar15;
  bool bVar16;
  uint uVar17;
  byte local_38;

  uVar4 = priv->fvco_tg;
  uVar3 = priv->config.xtal;
  uVar1 = priv->config.xtal >> 1;
  uVar12 = priv->config.xtal * 2;
  if (priv->config.xtal == 24000) {
    iVar10 = priv->fvco_tg / priv->ldiv;
    if (0x176e < iVar10 - 0x518b1U) {
      cVar9 = '\0';
      uVar13 = 48000;
      goto LAB_00089804;
    }
    uVar6 = 0x5dc;
    cVar9 = '\0';
    uVar13 = 24000;
LAB_00089808:
    uVar5 = uVar4 / uVar6;
    extraout_r1_00 = uVar4 % uVar6;
    uVar6 = (extraout_r1_00 << 0xc) / uVar6;
  }
  else {
    if (priv->config.xtal == 27000) {
      iVar10 = (priv->fvco_tg / 27000 -
               (((int)((ulonglong)(priv->fvco_tg >> 2) * 0x4dac1b9d >>
                      0x20) << 0x15) >> 0x1f)) * 27000;
      if (((iVar10 + 10U < priv->fvco_tg) &&
          (priv->fvco_tg < iVar10 + 0x3f2U)) ||
         ((priv->fvco_tg < iVar10 - 10U &&
          (iVar10 - 0x3f2U < priv->fvco_tg)))) {
        cVar9 = '\x02';
        uVar13 = 18000;
      }
      else if ((iVar10 + 0x3fcU < priv->fvco_tg) &&
              (priv->fvco_tg < iVar10 + 0x7e4U)) {
        cVar9 = '\x01';
        uVar13 = 18000;
      }
      else if (priv->fvco_tg < iVar10 - 0x3fcU) {
        cVar9 = iVar10 - 0x7e4U < priv->fvco_tg;
        uVar13 = 18000;
        if (!(bool)cVar9) {
          uVar13 = 54000;
        }
      }
      else {
        cVar9 = '\0';
        uVar13 = 54000;
      }
LAB_00089804:
      uVar6 = uVar13 >> 4;
      goto LAB_00089808;
    }
    uVar13 = uVar12;
    if (uVar12 == 9000 || uVar12 == 27000) {
      uVar6 = uVar12 >> 3;
      iVar10 = priv->fvco_tg << 1;
      uVar5 = iVar10 / uVar6;
      extraout_r1 = iVar10 % uVar6;
      cVar9 = '\0';
      uVar6 = (extraout_r1 << 0xc) / uVar6;
    }
    else {
      cVar9 = '\0';
      if (uVar12 != 0x34bc) goto LAB_00089804;
      uVar5 = (priv->fvco_tg * 4) / 0xd2f;
      uVar6 = (((priv->fvco_tg * 4) % 0xd2f) * 0x1000) / 0xd2f;
    }
  }
  uVar15 = (uVar5 << 0x12) >> 0x16;
  uVar14 = uVar5 & 0xf;
  if ((uVar6 & 0xfff) - 0x21 < 0xfbf) {
    reg_data = (uint8_t)uVar6;
    bVar16 = true;
    local_38 = (byte)((uVar6 << 0x14) >> 0x1c) | 0x30;
    uVar6 = uVar13 * (uVar6 & 0xfff) >> 0x10;
  }
  else {
    if ((uVar6 & 0x800) != 0) {
      uVar15 = (uVar5 + 1) * 0x40000 >> 0x16;
      uVar14 = uVar5 + 1 & 0xf;
    }
    bVar16 = false;
    reg_data = 0x0;
    local_38 = 0x30;
    uVar6 = 0;
  }
  uVar6 = uVar13 * uVar15 + uVar6 + (uVar13 * uVar14 >> 4);
  if (uVar6 < 8000000) {
    uVar6 = (uVar6 * -4 + 32000000) / 0x9eb1;
  }
  else {
    uVar6 = -(((uVar6 + 0x3f85ee00) * 4) / 0x9eb1);
  }
  uVar7 = uVar6 + 0x100;
  uVar17 = uVar7 * 0x80000 >> 0x18;
  uVar5 = (uVar17 & 1) + (uVar7 >> 6) & 0xff;
  if (uVar3 == uVar13) {
    uVar17 = uVar17 - ((int)(uVar6 << 0x1b) >> 0x1f);
    m88tc6800_write_reg(priv, 0x4e,0x11);
    uVar8 = 0x11;
LAB_000898b0:
    uVar5 = uVar17 & 0xff;
    m88tc6800_write_reg(priv, 0x4f,uVar8);
    m88tc6800_write_reg(priv, 0x4e,0x10);
    uVar8 = 0x8;
  }
  else {
    if (uVar13 == uVar12 / 3) {
      m88tc6800_write_reg(priv, 0x4e,0x11);
      m88tc6800_write_reg(priv, 0x4f,0x33);
      m88tc6800_write_reg(priv, 0x4e,0x10);
      m88tc6800_write_reg(priv, 0x4f,0xb);
      m88tc6800_write_reg(priv, 0x4e,0x15);
      uVar5 = uVar5 + (uVar17 - ((int)(uVar6 << 0x1b) >> 0x1f)) & 0xff;
      m88tc6800_write_reg(priv, 0x4f,0x43);
      goto LAB_00089584;
    }
    if (uVar13 == uVar3 / 3) {
      uVar12 = uVar7 * 0x100000 >> 0x18;
      m88tc6800_write_reg(priv, 0x4e,0x11);
      m88tc6800_write_reg(priv, 0x4f,0x33);
      m88tc6800_write_reg(priv, 0x4e,0x10);
      m88tc6800_write_reg(priv, 0x4f,0x8);
      m88tc6800_write_reg(priv, 0x4e,0x15);
      uVar5 = ((uVar17 + uVar12) - ((int)(uVar6 << 0x1c) >> 0x1f)) + (uVar12 & 1) & 0xff;
      m88tc6800_write_reg(priv, 0x4f,0x63);
      goto LAB_00089584;
    }
    if (uVar1 == uVar13) {
      uVar17 = (uVar7 >> 4) - ((int)(uVar6 << 0x1c) >> 0x1f);
      m88tc6800_write_reg(priv, 0x4e,0x11);
      uVar8 = 0x22;
      goto LAB_000898b0;
    }
    m88tc6800_write_reg(priv, 0x4e,0x11);
    m88tc6800_write_reg(priv, 0x4f,0x11);
    m88tc6800_write_reg(priv, 0x4e,0x10);
    uVar8 = 0xb;
  }
  m88tc6800_write_reg(priv, 0x4f,uVar8);
  m88tc6800_write_reg(priv, 0x4e,0x15);
  m88tc6800_write_reg(priv, 0x4f,0x13);
LAB_00089584:
  if (bVar16) {
    m88tc6800_write_reg(priv, 0x4e,0x12);
    uVar5 = uVar5 - 1 & 0xff;
    m88tc6800_write_reg(priv, 0x4f,0x21);
  }
  else {
    m88tc6800_write_reg(priv, 0x4e,0x12);
    m88tc6800_write_reg(priv, 0x4f,0x0);
  }
  if (cVar9 == '\x01') {
    uVar5 = uVar5 >> 1;
  }
  else if (cVar9 == '\x02') {
    uVar5 = uVar5 >> 2;
  }
  if (uVar5 < 2) {
    uVar5 = 2;
  }
  bVar11 = (byte)uVar5;
  if (0xe < uVar5) {
    bVar11 = 0xf;
  }
  m88tc6800_write_reg(priv, 0x4e,0xa);
  m88tc6800_write_reg(priv, 0x4f,0x63);
  m88tc6800_write_reg(priv, 0x4e,0xf);
  m88tc6800_write_reg(priv, 0x4f,0x3d);
  m88tc6800_write_reg(priv, 0x4e,0xb);
  m88tc6800_write_reg(priv, 0x4f,0xa1);
  m88tc6800_write_reg(priv, 0x3d,0xff);
  m88tc6800_write_reg(priv, 0x4e,0x1c);
  m88tc6800_write_reg(priv, 0x4f,0x7e);
  bVar2 = (byte)(uVar14 << 3);
  if (bVar16) {
    m88tc6800_write_reg(priv, 0x4e,0x19);
    m88tc6800_write_reg(priv, 0x4f,bVar2 | 3);
    m88tc6800_write_reg(priv, 0x4e,0x19);
    m88tc6800_write_reg(priv, 0x4f,bVar2 | 7);
  }
  else {
    m88tc6800_write_reg(priv, 0x4e,0x19);
    m88tc6800_write_reg(priv, 0x4f,bVar2 | 2);
    m88tc6800_write_reg(priv, 0x4e,0x19);
    m88tc6800_write_reg(priv, 0x4f,bVar2 | 6);
  }
  m88tc6800_write_reg(priv, 0x4e,0x17);
  m88tc6800_write_reg(priv, 0x4f,(byte)(uVar15 >> 8) | 0xc);
  m88tc6800_write_reg(priv, 0x4e,0x18);
  m88tc6800_write_reg(priv, 0x4f,(uint8_t)uVar15);
  m88tc6800_write_reg(priv, 0x4e,0x1a);
  m88tc6800_write_reg(priv, 0x4f,local_38);
  m88tc6800_write_reg(priv, 0x4e,0x1b);
  m88tc6800_write_reg(priv, 0x4f,reg_data);
  m88tc6800_write_reg(priv, 0x4e,0xe);
  m88tc6800_write_reg(priv, 0x4f,0x58);
  m88tc6800_write_reg(priv, 0x4e,0x14);
  m88tc6800_write_reg(priv, 0x4f,0x4c);
  m88tc6800_write_reg(priv, 0x4e,0x13);
  m88tc6800_write_reg(priv, 0x4f,bVar11 | 0x10);
}

int main() {
    for (uint32_t freq = 1; freq < 1000000; freq++) {
        init();
        TC6800_tuner_cfg_cxd2856.tuner_crystal = 27000;
        priv.config.xtal = 27000;
        printf("freq: %d, crystal: %d\n", freq, priv.config.xtal);
        _mt_fe_tn_set_LO_tc6800_cxd2856(freq, get_mixer_type_orig(freq));
        _mt_fe_tn_set_PLL_freq_tc6800_cxd2856();
        m88tc6800_set_lo(&priv, freq, m88tc6800_get_mixer_type(freq));
        m88tc6800_set_pll(&priv);
        finish();

        TC6800_tuner_cfg_cxd2856.tuner_crystal = 24000;
        priv.config.xtal = 24000;
        printf("freq: %d, crystal: %d\n", freq, priv.config.xtal);
        _mt_fe_tn_set_LO_tc6800_cxd2856(freq, get_mixer_type_orig(freq));
        _mt_fe_tn_set_PLL_freq_tc6800_cxd2856();
        m88tc6800_set_lo(&priv, freq, m88tc6800_get_mixer_type(freq));
        m88tc6800_set_pll(&priv);
        finish();
    }
}
