#include "common.h"

void _mt_fe_tn_set_BB_tc6800_cxd2856(void)

{
  uint8_t uVar1;
  
                    /* Unresolved local var: uint32_t bandwidth@[???] */
  __gnu_mcount_nc();
  if (TC6800_tuner_cfg_cxd2856.tuner_bandwidth == 0x6a4) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x59,0x9);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x29,0xae);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x86,0x3c);
    return;
  }
  if (TC6800_tuner_cfg_cxd2856.tuner_bandwidth == 6000) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x59,0xa);
    uVar1 = 0xaa;
  }
  else {
    if (TC6800_tuner_cfg_cxd2856.tuner_bandwidth == 7000) {
      uVar1 = 0xb;
    }
    else {
      if (TC6800_tuner_cfg_cxd2856.tuner_bandwidth == 10000) {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x59,0xd);
        uVar1 = 0xa6;
        goto LAB_00089b0c;
      }
      uVar1 = 0xc;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x59,uVar1);
    uVar1 = 0xa8;
  }
LAB_00089b0c:
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x29,uVar1);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x86,0x12);
  return;
}

void m88tc6800_set_bandwidth(struct m88tc6800_priv *priv)
{
    if (priv->bandwidth_hz == 1700) {
        m88tc6800_write_reg(priv, 0x59, 0x09);
        m88tc6800_write_reg(priv, 0x29, 0xae);
        m88tc6800_write_reg(priv, 0x86, 0x3c);
    }
    else if (priv->bandwidth_hz == 6000) {
        m88tc6800_write_reg(priv, 0x59, 0x0a);
        m88tc6800_write_reg(priv, 0x29, 0xaa);
        m88tc6800_write_reg(priv, 0x86, 0x12);
    }
    else if (priv->bandwidth_hz == 7000) {
        m88tc6800_write_reg(priv, 0x59, 0x0b);
        m88tc6800_write_reg(priv, 0x29, 0xa8);
        m88tc6800_write_reg(priv, 0x86, 0x12);
    }
    else if (priv->bandwidth_hz == 8000) {
        m88tc6800_write_reg(priv, 0x59, 0x0c);
        m88tc6800_write_reg(priv, 0x29, 0xa8);
        m88tc6800_write_reg(priv, 0x86, 0x12);
    }
    else {
        m88tc6800_write_reg(priv, 0x59, 0x0d);
        m88tc6800_write_reg(priv, 0x29, 0xa6);
        m88tc6800_write_reg(priv, 0x86, 0x12);
    }
}

int main() {
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};
    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
        uint32_t bw = bw_list[i];
        init();
        TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
        priv.bandwidth_hz = bw;
        printf("bw: %d\n", bw);
        _mt_fe_tn_set_BB_tc6800_cxd2856();
        m88tc6800_set_bandwidth(&priv);
        finish();
    }
}
