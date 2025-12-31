#include "common.h"

void _mt_fe_tn_set_DAC_tc6800_cxd2856(uint32_t freq_KHz)

{
  uint32_t uVar1;
  uint extraout_r0 = freq_KHz;
  int iVar2;
  int iVar3;
  uint uVar2;
  char cVar4;
  int extraout_r1;
  int extraout_r1_00;
  uint uVar6;
  uint uVar7;
  
                    /* Unresolved local var: uint32_t DACFreq_KHz@[???]
                       Unresolved local var: uint32_t fc@[???]
                       Unresolved local var: uint32_t fadc@[???]
                       Unresolved local var: uint32_t fsd@[???]
                       Unresolved local var: uint32_t f2d@[???]
                       Unresolved local var: uint8_t tempnumber@[???]
                       Unresolved local var: uint8_t flt_bit@[???]
                       Unresolved local var: uint8_t gain_bit@[???]
                       Unresolved local var: uint8_t R_22@[???]
                       Unresolved local var: uint32_t FreqTrue108_Hz@[???]
                       Unresolved local var: uint32_t f1@[???]
                       Unresolved local var: uint32_t f2@[???]
                       Unresolved local var: uint32_t delta1@[???]
                       Unresolved local var: uint32_t Totalnum1@[???]
                       Unresolved local var: uint32_t cntT@[???]
                       Unresolved local var: uint32_t cntin@[???]
                       Unresolved local var: uint32_t NCOI@[???]
                       Unresolved local var: uint32_t z0@[???]
                       Unresolved local var: uint32_t z1@[???]
                       Unresolved local var: uint32_t z2@[???]
                       Unresolved local var: uint32_t tmp@[???]
                       Unresolved local var: uint32_t f1f2number@[???] */
  __gnu_mcount_nc();
  uVar1 = TC6800_tuner_cfg_cxd2856.tuner_dac;
  if (TC6800_tuner_cfg_cxd2856.tuner_dac < 0x1195) {
    cVar4 = '@';
  }
  else {
    cVar4 = -0x80;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856
            (0x22,cVar4 + TC6800_tuner_cfg_cxd2856.tuner_dac_gain * '\b' + 0x5);
  _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x20,0x3,0x6,0x5);
  if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 24000) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xd);
LAB_0008a204:
    if (extraout_r0 != 0xf37ff) {
      if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 24000) {
        if (0x4a36 < (extraout_r0 + ((extraout_r0 >> 3) / 0xd2f) * -27000) - 0xfa1) {
          _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
          _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x12);
          if (extraout_r0 % 30000 - 0xfa1 < 21999) {
            uVar7 = 120000;
            uVar6 = 120000000;
          }
          else {
            _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
            _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x16);
            if (extraout_r0 % 0x7e90 - 0xfa1 < 0x5f4f) {
              uVar7 = 0x1fa40;
              uVar6 = 0x7b98a00;
            }
            else {
              _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
              _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xf);
              if ((extraout_r0 + ((extraout_r0 >> 3) / 0xdc5) * -0x6e28) - 0xfa1 < 0x4ee7) {
                uVar7 = 0x1b8a0;
                uVar6 = 0x6b93100;
              }
              else {
                _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
                _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x11);
                uVar7 = 0x1cb60;
                uVar6 = 0x7026f00;
              }
            }
          }
          goto LAB_0008a048;
        }
      }
      else if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 27000) {
        if (extraout_r0 % 27000 - 0xfa1 < 18999) {
          uVar7 = 0x1a5e0;
          uVar6 = 108000000;
        }
        else {
          _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
          _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xc);
          if (extraout_r0 % 0x7404 - 0xfa1 < 0x54c3) {
            uVar7 = 0x1d010;
            uVar6 = 0x714be80;
          }
          else {
            _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
            _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x10);
            if (extraout_r0 % 0x7e90 - 0xfa1 < 0x5f4f) {
              uVar7 = 0x1fa40;
              uVar6 = 0x7b98a00;
            }
            else {
              _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
              _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xa);
              if (extraout_r0 % 0x6ebe - 0xfa1 < 0x4f7d) {
                uVar7 = 0x1baf8;
                uVar6 = 0x6c258c0;
              }
              else {
                _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
                _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xb);
                uVar7 = 0x1c584;
                uVar6 = 0x6eb8ba0;
              }
            }
          }
        }
        if (extraout_r0 == 0x79ac9) {
          _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
          _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x4);
        }
        goto LAB_0008a048;
      }
    }
  }
  else if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 27000) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x6);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x8);
    goto LAB_0008a204;
  }
  uVar7 = 0x1a5e0;
  uVar6 = 108000000;
LAB_0008a048:
  extraout_r1 = __aeabi_uidivmod(uVar1 * 0x7d000,uVar6);
  iVar2 = __aeabi_uidiv(extraout_r1 << 5,uVar6);
  iVar3 = __aeabi_uidiv(uVar1 * 0x7d000,uVar6);
  iVar2 = (iVar2 + iVar3 * 0x20) * 4;
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xfa,(uint8_t)((uint)iVar2 >> 8));
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xfb,(uint8_t)iVar2);
  if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x3) {
    iVar2 = ((TC6800_tuner_cfg_cxd2856.tuner_bandwidth >> 1) - 0x96) * 0x1a5e0;
  }
  else if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x4) {
    if (TC6800_tuner_cfg_cxd2856.tuner_bandwidth == 8000) {
      iVar2 = 0x18c89ac0;
    }
    else {
      iVar2 = ((TC6800_tuner_cfg_cxd2856.tuner_bandwidth >> 1) - 100) * 0x1a5e0;
    }
  }
  else {
    if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x1) {
      iVar2 = (TC6800_tuner_cfg_cxd2856.tuner_bandwidth >> 1) - 0x8c;
    }
    else {
      iVar2 = (TC6800_tuner_cfg_cxd2856.tuner_bandwidth >> 1) - 100;
    }
    iVar2 = iVar2 * 0x1a5e0;
  }
  iVar3 = __aeabi_uidiv(iVar2,uVar7);
  iVar2 = (0x1000 - iVar3) * 0x8000;
  uVar2 = __aeabi_uidiv(iVar2,iVar3);
  extraout_r1_00 = __aeabi_uidivmod(iVar2,iVar3);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xe0,(byte)((uint)(extraout_r1_00 << 0x14) >> 0x1c));
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xe1,(uint8_t)extraout_r1_00);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xe2,(uint8_t)((uint)iVar3 >> 8));
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xe3,(uint8_t)iVar3);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xe4,(uint8_t)((ushort)(undefined2)uVar2 >> 8));
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xe5,(uint8_t)(undefined2)uVar2);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xef,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xf0,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xf1,0x8);
  iVar2 = ((uint)(iVar3 << 0xf) >> 0xb) - 0x8000;
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xf2,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xf3,(uint8_t)((uint)iVar2 >> 8));
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xf4,(uint8_t)iVar2);
  return;
}

void m88tc6800_set_dac(struct m88tc6800_priv *priv, uint32_t freq_khz)
{
  uint32_t uVar1 = 0x11da;
  uint extraout_r0 = freq_khz;
  int iVar2;
  int iVar3;
  uint uVar2;
  char cVar4;
  int extraout_r1;
  int extraout_r1_00;
  uint uVar6;
  uint uVar7;
  
                    /* Unresolved local var: uint32_t DACFreq_KHz@[???]
                       Unresolved local var: uint32_t fc@[???]
                       Unresolved local var: uint32_t fadc@[???]
                       Unresolved local var: uint32_t fsd@[???]
                       Unresolved local var: uint32_t f2d@[???]
                       Unresolved local var: uint8_t tempnumber@[???]
                       Unresolved local var: uint8_t flt_bit@[???]
                       Unresolved local var: uint8_t gain_bit@[???]
                       Unresolved local var: uint8_t R_22@[???]
                       Unresolved local var: uint32_t FreqTrue108_Hz@[???]
                       Unresolved local var: uint32_t f1@[???]
                       Unresolved local var: uint32_t f2@[???]
                       Unresolved local var: uint32_t delta1@[???]
                       Unresolved local var: uint32_t Totalnum1@[???]
                       Unresolved local var: uint32_t cntT@[???]
                       Unresolved local var: uint32_t cntin@[???]
                       Unresolved local var: uint32_t NCOI@[???]
                       Unresolved local var: uint32_t z0@[???]
                       Unresolved local var: uint32_t z1@[???]
                       Unresolved local var: uint32_t z2@[???]
                       Unresolved local var: uint32_t tmp@[???]
                       Unresolved local var: uint32_t f1f2number@[???] */
  m88tc6800_write_reg(priv, 0x22,0x95);
  m88tc6800_set_reg_bits(priv, 0x20,0x3,0x5,0x6);
  if (priv->config.xtal == 24000) {
    m88tc6800_write_reg(priv, 0x4e,0x6);
    m88tc6800_write_reg(priv, 0x4f,0xd);
LAB_0008a204:
    if (extraout_r0 != 0xf37ff) {
      if (priv->config.xtal == 24000) {
        if (0x4a36 < (extraout_r0 + ((extraout_r0 >> 3) / 0xd2f) * -27000) - 0xfa1) {
          m88tc6800_write_reg(priv, 0x4e,0x6);
          m88tc6800_write_reg(priv, 0x4f,0x12);
          if (extraout_r0 % 30000 - 0xfa1 < 21999) {
            uVar7 = 120000;
            uVar6 = 120000000;
          }
          else {
            m88tc6800_write_reg(priv, 0x4e,0x6);
            m88tc6800_write_reg(priv, 0x4f,0x16);
            if (extraout_r0 % 0x7e90 - 0xfa1 < 0x5f4f) {
              uVar7 = 0x1fa40;
              uVar6 = 0x7b98a00;
            }
            else {
              m88tc6800_write_reg(priv, 0x4e,0x6);
              m88tc6800_write_reg(priv, 0x4f,0xf);
              if ((extraout_r0 + ((extraout_r0 >> 3) / 0xdc5) * -0x6e28) - 0xfa1 < 0x4ee7) {
                uVar7 = 0x1b8a0;
                uVar6 = 0x6b93100;
              }
              else {
                m88tc6800_write_reg(priv, 0x4e,0x6);
                m88tc6800_write_reg(priv, 0x4f,0x11);
                uVar7 = 0x1cb60;
                uVar6 = 0x7026f00;
              }
            }
          }
          goto LAB_0008a048;
        }
      }
      else if (priv->config.xtal == 27000) {
        if (extraout_r0 % 27000 - 0xfa1 < 18999) {
          uVar7 = 0x1a5e0;
          uVar6 = 108000000;
        }
        else {
          m88tc6800_write_reg(priv, 0x4e,0x6);
          m88tc6800_write_reg(priv, 0x4f,0xc);
          if (extraout_r0 % 0x7404 - 0xfa1 < 0x54c3) {
            uVar7 = 0x1d010;
            uVar6 = 0x714be80;
          }
          else {
            m88tc6800_write_reg(priv, 0x4e,0x6);
            m88tc6800_write_reg(priv, 0x4f,0x10);
            if (extraout_r0 % 0x7e90 - 0xfa1 < 0x5f4f) {
              uVar7 = 0x1fa40;
              uVar6 = 0x7b98a00;
            }
            else {
              m88tc6800_write_reg(priv, 0x4e,0x6);
              m88tc6800_write_reg(priv, 0x4f,0xa);
              if (extraout_r0 % 0x6ebe - 0xfa1 < 0x4f7d) {
                uVar7 = 0x1baf8;
                uVar6 = 0x6c258c0;
              }
              else {
                m88tc6800_write_reg(priv, 0x4e,0x6);
                m88tc6800_write_reg(priv, 0x4f,0xb);
                uVar7 = 0x1c584;
                uVar6 = 0x6eb8ba0;
              }
            }
          }
        }
        if (extraout_r0 == 0x79ac9) {
          m88tc6800_write_reg(priv, 0x4e,0x6);
          m88tc6800_write_reg(priv, 0x4f,0x4);
        }
        goto LAB_0008a048;
      }
    }
  }
  else if (priv->config.xtal == 27000) {
    m88tc6800_write_reg(priv, 0x4e,0x6);
    m88tc6800_write_reg(priv, 0x4f,0x8);
    goto LAB_0008a204;
  }
  uVar7 = 0x1a5e0;
  uVar6 = 108000000;
LAB_0008a048:
  extraout_r1 = (uVar1 * 0x7d000) % uVar6;
  iVar2 = (extraout_r1 << 5) / uVar6;
  iVar3 = (uVar1 * 0x7d000) / uVar6;
  iVar2 = (iVar2 + iVar3 * 0x20) * 4;
  m88tc6800_write_reg(priv, 0xfa,(uint8_t)((uint)iVar2 >> 8));
  m88tc6800_write_reg(priv, 0xfb,(uint8_t)iVar2);
  iVar2 = (priv->bandwidth_hz >> 1) - 100;
  iVar2 = iVar2 * 0x1a5e0;
  iVar3 = iVar2 / uVar7;
  iVar2 = (0x1000 - iVar3) * 0x8000;
  uVar2 = (unsigned)iVar2 / iVar3;
  extraout_r1_00 = (unsigned)iVar2 % iVar3;
  m88tc6800_write_reg(priv, 0xe0,(byte)((uint)(extraout_r1_00 << 0x14) >> 0x1c));
  m88tc6800_write_reg(priv, 0xe1,(uint8_t)extraout_r1_00);
  m88tc6800_write_reg(priv, 0xe2,(uint8_t)((uint)iVar3 >> 8));
  m88tc6800_write_reg(priv, 0xe3,(uint8_t)iVar3);
  m88tc6800_write_reg(priv, 0xe4,(uint8_t)((ushort)(undefined2)uVar2 >> 8));
  m88tc6800_write_reg(priv, 0xe5,(uint8_t)(undefined2)uVar2);
  m88tc6800_write_reg(priv, 0xef,0x0);
  m88tc6800_write_reg(priv, 0xf0,0x0);
  m88tc6800_write_reg(priv, 0xf1,0x8);
  iVar2 = ((uint)(iVar3 << 0xf) >> 0xb) - 0x8000;
  m88tc6800_write_reg(priv, 0xf2,0x0);
  m88tc6800_write_reg(priv, 0xf3,(uint8_t)((uint)iVar2 >> 8));
  m88tc6800_write_reg(priv, 0xf4,(uint8_t)iVar2);
}

int main() {
    uint32_t bw_list[] = {1700, 6000, 7000, 8000, 10000};
    for (int i = 0; i < sizeof(bw_list) / sizeof(bw_list[0]); i++) {
        for (uint32_t freq = 0; freq < 1000000; freq++) {
            uint32_t bw = bw_list[i];
            init();
            TC6800_tuner_cfg_cxd2856.tuner_bandwidth = bw;
            priv.bandwidth_hz = bw;
            priv.config.xtal = 27000;
            printf("freq: %d, bw: %d\n", freq, bw);
            _mt_fe_tn_set_DAC_tc6800_cxd2856(freq);
            m88tc6800_set_dac(&priv, freq);
            finish();
        }
    }
}
