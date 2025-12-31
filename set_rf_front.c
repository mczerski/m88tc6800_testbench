#include "common.h"

/* WARNING: Enum "anon_enum_32": Some values do not have unique names */
/* WARNING: Enum "sony_ascot3_tv_system_t": Some values do not have unique names */
/* WARNING: Enum "sony_helene_tv_system_t": Some values do not have unique names */

void _mt_fe_tn_set_RF_front_tc6800_cxd2856(uint32_t freq_KHz)

{
  bool bVar1;
  bool bVar2;
  uint extraout_r0 = freq_KHz;
  byte bVar3;
  uint8_t uVar4;
  byte local_21 [5];
  
                    /* Unresolved local var: uint32_t fl@[???]
                       Unresolved local var: uint32_t fm@[???]
                       Unresolved local var: uint8_t buf2@[???] */
  __gnu_mcount_nc();
  if (TC6800_tuner_cfg_cxd2856.tuner_int_im == 0x0) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x88,0x27);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x89,0x2b);
    uVar4 = 0x67;
LAB_0008a8bc:
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x8a,uVar4);
    local_21[0] = 0x22;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x69);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x12);
LAB_0008a694:
    if (1 < (uint)TC6800_tuner_cfg_cxd2856.tuner_mode - 1) goto LAB_0008a6a4;
LAB_0008a7d8:
    if (TC6800_tuner_cfg_cxd2856.tuner_int_lt < 2) goto LAB_0008a6a4;
    if (TC6800_tuner_cfg_cxd2856.tuner_int_im == 0x2) {
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x8b,local_21);
      local_21[0] = local_21[0] | 0x88;
    }
    else {
      local_21[0] = 0xaa;
    }
    bVar3 = local_21[0];
    if (TC6800_tuner_cfg_cxd2856.tuner_custom_cfg == 1) {
      bVar3 = 0xaa;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x8b,bVar3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xfd,0x12);
    if (extraout_r0 < 112001) goto LAB_0008a828;
LAB_0008a6d8:
    if (extraout_r0 < 334001) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x7f,0x4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x92,0x8c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x87,0xf0);
      goto LAB_0008a70c;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7f,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x92,0x8c);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x87,0xf0);
    if (extraout_r0 < 451001) goto LAB_0008a70c;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x90,0x4a);
  }
  else {
    if (TC6800_tuner_cfg_cxd2856.tuner_int_im == 0x1) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x88,0x1b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x89,0x2b);
      uVar4 = 0x1b;
      goto LAB_0008a8bc;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x88,0x2b);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x89,0x2b);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x8a,0xab);
    if ((extraout_r0 < 602001) && (TC6800_tuner_cfg_cxd2856.tuner_application != 0x1)) {
      local_21[0] = 0x55;
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x69);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x2d);
      goto LAB_0008a694;
    }
    local_21[0] = 0x11;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x69);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x9);
    if ((uint)TC6800_tuner_cfg_cxd2856.tuner_mode - 1 < 2) goto LAB_0008a7d8;
LAB_0008a6a4:
    bVar3 = local_21[0];
    if (TC6800_tuner_cfg_cxd2856.tuner_custom_cfg == 1) {
      bVar3 = 0xaa;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x8b,bVar3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xfd,0x1a);
    if (112000 < extraout_r0) goto LAB_0008a6d8;
LAB_0008a828:
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7f,0x8);
    if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x1) {
      uVar4 = 0xac;
    }
    else {
      uVar4 = 0x8c;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x92,uVar4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x87,0xf0);
LAB_0008a70c:
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x90,0x49);
  }
  if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x0) {
    uVar4 = 0x84;
  }
  else {
    uVar4 = 0x74;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xaa,uVar4);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xa9,0xf6);
  if ((uint)TC6800_tuner_cfg_cxd2856.tuner_application - 3 < 2) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x98,0xf7);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x99,0xa5);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x26,0x14);
    if (TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp != 0x1) {
      return;
    }
    if (334000 < extraout_r0) {
      if (extraout_r0 < 474001) {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,0x29);
        return;
      }
      if (extraout_r0 < 858001) {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,0x15);
        return;
      }
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,0x1);
    return;
  }
  if (TC6800_tuner_cfg_cxd2856.tuner_application != 1) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x98,0xf8);
    if (extraout_r0 - 700001 < 200000) {
      uVar4 = 0xa5;
    }
    else {
      uVar4 = 0xb6;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x99,uVar4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x26,0x11);
    if (TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp != 0x1) {
      return;
    }
    bVar1 = extraout_r0 - 610000 < 14001;
    bVar2 = extraout_r0 - 480000 < 12001;
    if (bVar1 || bVar2) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,0x15);
      if ((!bVar2 && (20000 < extraout_r0 - 800000 && !bVar1)) && (8000 < extraout_r0 - 366000)) {
LAB_0008aa38:
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xe);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xf);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x10);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1);
        return;
      }
    }
    else if (extraout_r0 - 366000 < 8001) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,0x29);
    }
    else {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,0x1);
      if (20000 < extraout_r0 - 800000) goto LAB_0008aa38;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xe);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xf);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x10);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x2);
    return;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x98,0xf5);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x99,0x94);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x26,0x14);
  if (TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp == 0x1) {
    if (extraout_r0 < 0x518b1) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,0x1);
      if (extraout_r0 < 0x1b581) goto LAB_0008a938;
    }
    else {
      if (extraout_r0 < 0x73b91) {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,0x29);
      }
      else {
        uVar4 = 0x1;
        if (extraout_r0 < 0xd1791) {
          uVar4 = 0x15;
        }
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x94,uVar4);
      }
      if (TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp != 0x1) {
LAB_0008a938:
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x13);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xb);
        return;
      }
    }
  }
  else if ((extraout_r0 < 0x1b581) || (0x518b0 < extraout_r0)) goto LAB_0008a938;
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x13);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x9);
  return;
}

static void m88tc6800_set_rf_frontend(struct m88tc6800_priv *priv, u32 freq_khz)
{
    m88tc6800_write_reg(priv, 0x88, 0x2b);
    m88tc6800_write_reg(priv, 0x89, 0x2b);
    m88tc6800_write_reg(priv, 0x8a, 0xab);
    m88tc6800_write_reg(priv, 0x39, 0x69);
    if (freq_khz <= 602000) {
        m88tc6800_write_reg(priv, 0x3a, 0x2d);
        m88tc6800_write_reg(priv, 0x8b, 0x55);
    }
    else {
        m88tc6800_write_reg(priv, 0x3a, 0x09);
        m88tc6800_write_reg(priv, 0x8b, 0x11);
    }
    m88tc6800_write_reg(priv, 0xfd, 0x1a);
    if (freq_khz > 112000) {
        if (freq_khz <= 334000) {
            m88tc6800_write_reg(priv, 0x7f, 0x04);
            m88tc6800_write_reg(priv, 0x92, 0x8c);
            m88tc6800_write_reg(priv, 0x87, 0xf0);
            m88tc6800_write_reg(priv, 0x90, 0x49);
        }
        else {
            m88tc6800_write_reg(priv, 0x7f, 0x00);
            m88tc6800_write_reg(priv, 0x92, 0x8c);
            m88tc6800_write_reg(priv, 0x87, 0xf0);
            if (freq_khz <= 451000) {
                m88tc6800_write_reg(priv, 0x90, 0x49);
            }
            else {
                m88tc6800_write_reg(priv, 0x90, 0x4a);
            }
        }
    }
    else {
        m88tc6800_write_reg(priv, 0x7f, 0x08);
        m88tc6800_write_reg(priv, 0x92, 0x8c);
        m88tc6800_write_reg(priv, 0x87, 0xf0);
        m88tc6800_write_reg(priv, 0x90, 0x49);
    }
    m88tc6800_write_reg(priv, 0xaa, 0x84);
    m88tc6800_write_reg(priv, 0xa9, 0xf6);
    m88tc6800_write_reg(priv, 0x98, 0xf8);
    if (freq_khz > 700000 && freq_khz <= 900000) {
        m88tc6800_write_reg(priv, 0x99, 0xa5);
    }
    else {
        m88tc6800_write_reg(priv, 0x99, 0xb6);
    }
    m88tc6800_write_reg(priv, 0x26, 0x11);
    if (freq_khz >= 366000 && freq_khz <= 374000) {
        m88tc6800_write_reg(priv, 0x94, 0x29);
    }
    else if ((freq_khz >= 480000 && freq_khz <= 492000) || (freq_khz >= 610000 && freq_khz <= 624000)) {
        m88tc6800_write_reg(priv, 0x94, 0x15);
    }
    else {
        m88tc6800_write_reg(priv, 0x94, 0x01);
    }
    m88tc6800_write_reg(priv, 0x39, 0x0e);
    m88tc6800_write_reg(priv, 0x3a, 0x04);
    m88tc6800_write_reg(priv, 0x39, 0x0f);
    m88tc6800_write_reg(priv, 0x3a, 0x04);
    m88tc6800_write_reg(priv, 0x39, 0x10);

    if ((freq_khz >= 366000 && freq_khz <= 374000) ||
            (freq_khz >= 480000 && freq_khz <= 492000) ||
            (freq_khz >= 610000 && freq_khz <= 624000) ||
            (freq_khz >= 800000 && freq_khz <= 820000)) {
        m88tc6800_write_reg(priv, 0x3a, 0x02);
    }
    else {
        m88tc6800_write_reg(priv, 0x3a, 0x01);
    }
}

int main() {
    for (uint32_t freq = 0; freq < 1000000; freq++) {
        init();
        printf("freq: %d\n", freq);
        _mt_fe_tn_set_RF_front_tc6800_cxd2856(freq);
        m88tc6800_set_rf_frontend(&priv, freq);
        finish();
    }
}
