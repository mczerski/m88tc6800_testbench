#include "common.h"

void _mt_fe_tn_preset_tc6800_cxd2856(void)

{
  uint8_t reg_data;
  bool bVar1;
  byte local_19 [5];
  
                    /* Unresolved local var: uint8_t buf@[???] */
  __gnu_mcount_nc();
  if ((unsigned)TC6800_tuner_cfg_cxd2856.tuner_mode - 1 < 2) {
    reg_data = 0x7d;
  }
  else {
    reg_data = 0x6d;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xb,reg_data);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xc,0xe3);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xd,0xc4);
  _mt_fe_tn_get_reg_tc6800_cxd2856(0x9a,local_19);
  local_19[0] = local_19[0] & 0xf;
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x9a,local_19[0]);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x9d,0x3f);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x31,0x97);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xab,0xd9);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xb0,0x9);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xbd,0x2);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xb9,0x99);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x58,0x11);
  if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 24000) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x77);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x11);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7e,0x12);
  }
  else if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 27000) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7e,0x13);
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x80,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x82,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x10,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x66,0x0);
  bVar1 = TC6800_tuner_cfg_cxd2856.tuner_application != 0x0;
  if (TC6800_tuner_cfg_cxd2856.tuner_application != 0x1) {
    bVar1 = TC6800_tuner_cfg_cxd2856.tuner_application != 0x3;
  }
  if (!bVar1 || (TC6800_tuner_cfg_cxd2856.tuner_application == 0x1 ||
                TC6800_tuner_cfg_cxd2856.tuner_application == 0x4)) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x5);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x6);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x9);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xa);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xb);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xc);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xd);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x11);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x12);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x15);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x16);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x17);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x18);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x19);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x8b);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2c);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x10);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x1);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xcb);
  }
  return;
}

static void m88tc6800_preset(struct m88tc6800_priv *priv)
{
    u8 reg_data;

    m88tc6800_write_reg(priv, 0x0b, 0x6d);
    m88tc6800_write_reg(priv, 0x0c, 0xe3);
    m88tc6800_write_reg(priv, 0x0d, 0xc4);
    m88tc6800_read_reg(priv, 0x9a, &reg_data);
    m88tc6800_write_reg(priv, 0x9a, reg_data & 0xf);
    m88tc6800_write_reg(priv, 0x9d, 0x3f);
    m88tc6800_write_reg(priv, 0x31, 0x97);
    m88tc6800_write_reg(priv, 0xab, 0xd9);
    m88tc6800_write_reg(priv, 0xb0, 0x09);
    m88tc6800_write_reg(priv, 0xbd, 0x02);
    m88tc6800_write_reg(priv, 0xb9, 0x99);
    m88tc6800_write_reg(priv, 0x58, 0x11);
    if (priv->config.xtal == 24000) {
        m88tc6800_write_reg(priv, 0x39, 0x77);
        m88tc6800_write_reg(priv, 0x3a, 0x11);
        m88tc6800_write_reg(priv, 0x7e, 0x12);
    }
    else if (priv->config.xtal == 27000) {
        m88tc6800_write_reg(priv, 0x7e, 0x13);
    }
    m88tc6800_write_reg(priv, 0x80, 0x00);
    m88tc6800_write_reg(priv, 0x82, 0x00);
    m88tc6800_write_reg(priv, 0x10, 0x00);
    m88tc6800_write_reg(priv, 0x66, 0x00);
}

int main() {
    for (uint32_t freq = 0; freq < 1000000; freq++) {
        init();
        TC6800_tuner_cfg_cxd2856.tuner_crystal = 27000;
        priv.config.xtal = 27000;
        printf("freq: %d, crystal: %d\n", freq, priv.config.xtal);
        _mt_fe_tn_preset_tc6800_cxd2856();
        m88tc6800_preset(&priv);
        finish();

        init();
        TC6800_tuner_cfg_cxd2856.tuner_crystal = 24000;
        priv.config.xtal = 24000;
        printf("freq: %d, crystal: %d\n", freq, priv.config.xtal);
        _mt_fe_tn_preset_tc6800_cxd2856();
        m88tc6800_preset(&priv);
        finish();
    }
}
