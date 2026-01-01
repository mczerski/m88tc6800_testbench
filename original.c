#include "common.h"
#include "original.h"

#define printk(...)
#define sony_sleep(ms)
struct _MT_FE_TN_Device_Settings_TC6800 TC6800_tuner_cfg_cxd2856 = {
  .tuner_mode = 0x0,
  .tuner_mcu_status = 0x0,
  .tuner_application = 0x0,
  .tuner_custom_cfg = 0,
  .tuner_signal_delay_en = 0x0,
  .tuner_signal_delay_ns = 0,
  .tuner_mixer_type = 0,
  .tuner_gpio_out = 0x0,
  .tuner_time = 0x112d838,
  .tuner_int_lt = 0x2,
  .tuner_dac_gain = 0x2,
  .tuner_int_im = 0x2,
  .tuner_dac = 0x11da,
  .tuner_crystal = 27000,
  .tuner_crystal_cap = 0x18,
  .tuner_clock_out = 0x1,
  .tuner_harmonic_imp = 0x1,
  .tuner_version = 0x7a,
  .tuner_fw_version = 0xc,
};

uint8_t tuner_terr_cable_debug = 0;

void __gnu_mcount_nc(void)
{
}

unsigned __aeabi_uidivmod(unsigned numerator, unsigned denominator)
{
    return numerator % denominator;
}

unsigned __aeabi_uidiv(unsigned numerator, unsigned denominator)
{
    return numerator / denominator;
}

uint32_t _mt_fe_tn_set_reg_tc6800_cxd2856(uint8_t reg_addr,uint8_t reg_data) {
    i2c_log[expected_i2c_op] = ('w' << 24) + (reg_addr << 8) + reg_data;
    expected_i2c_op++;
    return 0;
}

uint32_t _mt_fe_tn_get_reg_tc6800_cxd2856(uint8_t reg_addr,uint8_t *reg_data) {
    *reg_data = i2c_reg[reg_addr];
    i2c_log[expected_i2c_op] = ('r' << 24) + (reg_addr << 8) + *reg_data;
    expected_i2c_op++;
    return 0;
}

uint32_t _mt_fe_tn_set_reg_bit_tc6800_cxd2856
                   (uint8_t reg_addr,uint8_t data,uint8_t high_bit,uint8_t low_bit)

{
  uint8_t reg_addr_00 = reg_addr;
  int extraout_r1 = data;
  uint extraout_r2 = high_bit;
  uint uVar1;
  uint extraout_r3 = low_bit;
  uint uVar2;
  byte local_21;
  
                    /* Unresolved local var: uint8_t tmp@[???]
                       Unresolved local var: uint8_t value@[???] */
  __gnu_mcount_nc();
  uVar1 = extraout_r3;
  uVar2 = extraout_r2;
  if (extraout_r3 <= extraout_r2) {
    uVar1 = extraout_r2;
    uVar2 = extraout_r3;
  }
  uVar2 = (uVar2 + 7) - uVar1;
  local_21 = 0;
  _mt_fe_tn_get_reg_tc6800_cxd2856(reg_addr_00,&local_21);
  local_21 = local_21 & ~(byte)((int)(0xff << (uVar2 & 0xff) & 0xffU) >> (7 - uVar1 & 0xff)) |
             (byte)((int)(extraout_r1 << (uVar2 & 0xff) & 0xffU) >> (7 - uVar1 & 0xff));
  _mt_fe_tn_set_reg_tc6800_cxd2856(reg_addr_00,local_21);
  return 0;
}

uint32_t _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856
                   (uint8_t reg_addr_expand,uint8_t reg_addr,uint8_t reg_data,uint8_t high_bit,
                   uint8_t low_bit)

{
  byte reg_data_00;
  uint8_t reg_addr_00 = reg_addr_expand;
  uint8_t reg_data_01 = reg_addr;
  int extraout_r2 = reg_data;
  uint extraout_r3 = high_bit;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte local_31 [5];
  
                    /* Unresolved local var: uint8_t tmp@[???]
                       Unresolved local var: uint8_t value@[???]
                       Unresolved local var: uint8_t data@[???] */
  __gnu_mcount_nc();
  uVar2 = (uint)low_bit;
  local_31[0] = 0;
  uVar1 = uVar2;
  uVar3 = extraout_r3;
  if (uVar2 <= extraout_r3) {
    uVar1 = extraout_r3;
    uVar3 = uVar2;
  }
  uVar3 = (uVar3 + 7) - uVar1;
  _mt_fe_tn_set_reg_tc6800_cxd2856(reg_addr_00,reg_data_01);
  _mt_fe_tn_get_reg_tc6800_cxd2856(reg_addr_00 + 0x1,local_31);
  reg_data_00 = local_31[0] & ~(byte)((int)(0xff << (uVar3 & 0xff) & 0xffU) >> (7 - uVar1 & 0xff)) |
                (byte)((int)(extraout_r2 << (uVar3 & 0xff) & 0xffU) >> (7 - uVar1 & 0xff));
  local_31[0] = reg_data_00;
  _mt_fe_tn_set_reg_tc6800_cxd2856(reg_addr_00,reg_data_01);
  _mt_fe_tn_set_reg_tc6800_cxd2856(reg_addr_00 + 0x1,reg_data_00);
  return 0;
}

uint32_t mt_fe_tn_init_tc6800_cxd2856(void)

{
  return 0;
}

void _mt_fe_tn_preset_tc6800_cxd2856(void)

{
  uint8_t reg_data;
  bool bVar1;
  byte local_19 [5];
  
                    /* Unresolved local var: uint8_t buf@[???] */
  __gnu_mcount_nc();
  if ((uint)TC6800_tuner_cfg_cxd2856.tuner_mode - 1 < 2) {
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

void _mt_fe_tn_set_BB_tc6800_cxd2856(void)

{
  uint8_t uVar1;
  
                    /* Unresolved local var: uint32_t bandwidth@[???] */
  __gnu_mcount_nc();
  if (TC6800_tuner_cfg_cxd2856.tuner_bandwidth == 1700) {
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

void _mt_fe_tn_set_tune_tc6800_cxd2856(uint32_t freq_KHz,uint8_t mixer_sel,uint32_t wait_time)

{
  uint32_t freq_KHz_00 = freq_KHz;
  int ms;
  
                    /* Unresolved local var: char[34] __func__@[???] */
  __gnu_mcount_nc();
  if (0 < tuner_terr_cable_debug) {
    printk(&.LC4,"_mt_fe_tn_set_tune_tc6800_cxd2856",0x546,freq_KHz_00,1,ms);
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4,0x7f);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0xf8);
  _mt_fe_tn_preset_tc6800_cxd2856();
  _mt_fe_tn_set_RF_front_tc6800_cxd2856(freq_KHz_00);
  _mt_fe_tn_set_Mixer_tc6800_cxd2856(freq_KHz_00,0x1);
  _mt_fe_tn_set_LO_tc6800_cxd2856(freq_KHz_00,0x1);
  _mt_fe_tn_set_PLL_freq_tc6800_cxd2856();
  _mt_fe_tn_set_BB_tc6800_cxd2856();
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x0);
  _mt_fe_tn_set_DAC_tc6800_cxd2856(freq_KHz_00);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x40,0x1a);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x41,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x44,0x22);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x60,0x34);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x4);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xc2,0x1);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x0,0x1);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x0,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xc2,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
  sony_sleep(ms);
  return;
}

/* WARNING: Enum "anon_enum_32": Some values do not have unique names */
/* WARNING: Enum "sony_ascot3_tv_system_t": Some values do not have unique names */
/* WARNING: Enum "sony_helene_tv_system_t": Some values do not have unique names */

void mt_fe_tn_set_freq_tc6800_cxd2856(uint32_t freq_KHz)

{
  uint32_t freq_KHz_00 = freq_KHz;
  uint32_t uVar1;
  int iVar2;
  uint8_t uVar3;
  uint32_t wait_time;
  uint uVar4;
  uint32_t wait_time_00;
  uint32_t wait_time_01;
  uint uVar5;
  uint pcVar6;
  byte bVar6;
  char cVar7;
  uint8_t reg_data;
  uint16_t uVar8;
  uint uVar9;
  bool bVar10;
  bool bVar11;
  byte local_37;
  byte local_36;
  byte local_35;
  byte local_34;
  byte local_33;
  uint8_t local_32;
  byte local_31 [5];
  
                    /* Unresolved local var: uint32_t mt_ret@[???]
                       Unresolved local var: uint8_t sysmon_on@[???]
                       Unresolved local var: uint8_t buf@[???]
                       Unresolved local var: uint8_t mixer_sel@[???]
                       Unresolved local var: uint32_t buf_freq@[???]
                       Unresolved local var: uint8_t buf1@[???]
                       Unresolved local var: uint8_t buf2@[???]
                       Unresolved local var: char[33] __func__@[???] */
  __gnu_mcount_nc();
  local_37 = 0;
  local_36 = 0;
  local_35 = 0;
  if (0 < tuner_terr_cable_debug) {
    printk(&.LC17,"mt_fe_tn_set_freq_tc6800_cxd2856",0x9ac,
           TC6800_tuner_cfg_cxd2856.tuner_application,freq_KHz_00);
  }
  TC6800_tuner_cfg_cxd2856.tuner_freq = freq_KHz_00;
  uVar1 = mt_fe_tn_init_tc6800_cxd2856();
  if (uVar1 == 0) {
    if (0 < tuner_terr_cable_debug) {
      printk(&.LC16,"mt_fe_tn_set_freq_tc6800_cxd2856",0x9b7);
    }
  }
  else if (-1 < tuner_terr_cable_debug) {
    printk(&.LC18,"mt_fe_tn_set_freq_tc6800_cxd2856",0x9b3);
  }
  _mt_fe_tn_get_reg_tc6800_cxd2856(0x3e,&local_37);
  uVar5 = local_37 & 0x1e;
  local_37 = (byte)uVar5;
  if (uVar5 == 0x1e) {
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x3c,0x0,0x7,0x7);
    local_37 = TC6800_tuner_cfg_cxd2856.tuner_application;
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x3e,TC6800_tuner_cfg_cxd2856.tuner_application,0x4,0x1);
  }
  else {
    uVar9 = (uint)TC6800_tuner_cfg_cxd2856.tuner_application;
    uVar5 = uVar5 >> 1;
    local_37 = (byte)uVar5;
    if (uVar5 != uVar9) {
      if (uVar5 == 3) {
        if (uVar9 != 4) goto LAB_0008b74c;
        if (TC6800_tuner_cfg_cxd2856.tuner_gpio_out == 0x0) {
          _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x37,0x6,0x2,0x0);
        }
      }
      else if (uVar9 == 3 && uVar5 == 4) {
        _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x37,0x0,0x2,0x1);
      }
      else {
LAB_0008b74c:
        _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x3c,0x0,0x7,0x7);
      }
      local_37 = TC6800_tuner_cfg_cxd2856.tuner_application;
      _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x3e,TC6800_tuner_cfg_cxd2856.tuner_application,0x4,0x1);
    }
  }
                    /* Unresolved local var: uint8_t buf@[???] */
  local_31[0] = 0;
  _mt_fe_tn_get_reg_tc6800_cxd2856(0x7,local_31);
  bVar6 = local_31[0] & 8;
  if ((local_31[0] & 8) == 0) {
    local_31[0] = bVar6;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xc,0x63);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7,0xd);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xc,0xe3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x11,bVar6);
  }
  else {
    local_31[0] = bVar6;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7,0xd);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x11,0x0);
  }
  uVar8 = TC6800_tuner_cfg_cxd2856.tuner_mixer_type;
  if (((TC6800_tuner_cfg_cxd2856.tuner_mixer_type != 1) &&
      (TC6800_tuner_cfg_cxd2856.tuner_mixer_type != 2)) &&
     (TC6800_tuner_cfg_cxd2856.tuner_mixer_type != 3)) {
    if (freq_KHz_00 < 334001) {
      uVar8 = 2;
    }
    else if (TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp == 0x1) {
      if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x0) {
        uVar5 = freq_KHz_00 - 610000;
        bVar11 = 13999 < uVar5;
        bVar10 = uVar5 == 14000;
        if (14000 < uVar5) {
          bVar11 = 19999 < freq_KHz_00 - 800000;
          bVar10 = freq_KHz_00 - 800000 == 20000;
        }
        if ((bVar11 && !bVar10) && (12000 < freq_KHz_00 - 480000)) {
          uVar8 = 1;
          if (freq_KHz_00 - 366000 < 8001) {
            uVar8 = 3;
          }
          goto LAB_0008b808;
        }
      }
      uVar8 = 3;
    }
    else {
      uVar8 = 1;
    }
  }
LAB_0008b808:
  _mt_fe_tn_get_reg_tc6800_cxd2856(0x3c,&local_37);
  bVar6 = local_37 & 0x80;
  local_37 = local_37 & 0x80;
  if (bVar6 == 0) {
                    /* Unresolved local var: uint8_t data1@[???]
                       Unresolved local var: uint8_t data2@[???]
                       Unresolved local var: uint8_t data3@[???]
                       Unresolved local var: uint8_t i@[???]
                       Unresolved local var: uint8_t buf@[???]
                       Unresolved local var: char[37] __func__@[???] */
    local_34 = 0;
    local_33 = 0;
    local_32 = 0x0;
    if (0 < tuner_terr_cable_debug) {
      printk(&.LC19,"_mt_fe_tn_poweron_set_tc6800_cxd2856",0x57c);
    }
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x3c,0x1,0x0,0x0);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x55,0x1,0x0,0x0);
    if (TC6800_tuner_cfg_cxd2856.tuner_clock_out == 0x1) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x16,0x80);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x17,0xf3);
    }
    else {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x16,0x0);
    }
    uVar3 = TC6800_tuner_cfg_cxd2856.tuner_crystal_cap;
    local_31[0] = TC6800_tuner_cfg_cxd2856.tuner_crystal_cap;
    if (TC6800_tuner_cfg_cxd2856.tuner_crystal_cap != 0x18) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x1a,0x4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x1b,uVar3);
      bVar6 = local_31[0];
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x1a,0x5);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x1b,bVar6);
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xe,0xa4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xe9);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x68,0xf);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x69,0xf1);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x76,0x30);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x78,0x25);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x79,0x1f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7b,0x0);
    if ((uint)TC6800_tuner_cfg_cxd2856.tuner_application - 3 < 2) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb1,0x1a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb2,0x6f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb3,0x34);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb4,0x45);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb5,0x1a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb6,0x6f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xba,0x9a);
    }
    else {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb1,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb2,0xb2);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb3,0x54);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb4,0x6e);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb5,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb6,0xb2);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xba,0x90);
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x27,0xb4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x25,0x2a);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x84,0x20);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0xfc,0x1,0x5,0x5);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x2a,0x1,0x1,0x0);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0xa7,0x0,0x2,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x2c,0xa);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xc7,0x2);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xc6,0x80);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xad,0xa);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xfd,0x1a);
    uVar3 = TC6800_tuner_cfg_cxd2856.tuner_application;
    if ((uint)TC6800_tuner_cfg_cxd2856.tuner_application - 3 < 2) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xc7,0x3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x30,0x2f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x5);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x6);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4e);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x7);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xc);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x9);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xa);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xb);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x27);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xc);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xd);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x11);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x18);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x12);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x6a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x13);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xc);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x7);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x15);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x16);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x17);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x35);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x18);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x19);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x18);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xd);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x24);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1d);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xe);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xf);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x10);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xa);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x29);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xee);
      uVar3 = 0xd;
    }
    else if (TC6800_tuner_cfg_cxd2856.tuner_application == 1) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xc7,uVar3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x30,0x2f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x5);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x6);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x7);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xc);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x9);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xa);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xb);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,uVar3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xc);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xd);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x7f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x11);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x12);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xb);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x13);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x9);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x7);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x15);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x16);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x17);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x5);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x18);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x19);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x7f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xd);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x12);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x28);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1d);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x2e);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xe);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xf);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x10);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xa);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x20);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x2);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xcc);
      uVar3 = 0xf;
    }
    else {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xc7,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x5);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x6);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x7);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xd);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x9);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x9);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xa);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xb);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xc);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xd);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x7f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x8);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x1b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xd);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xe);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xf);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x10);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xa);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x10);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xcc);
      uVar3 = 0x10;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7c,uVar3);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x35,0x0,0x7,0x4);
    if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x3) {
      _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x37,0x0,0x2,0x1);
    }
    else if (TC6800_tuner_cfg_cxd2856.tuner_gpio_out == 0x0) {
      _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x37,0x6,0x2,0x0);
    }
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0xbd,0x1,0x7,0x7);
    if ((uint)TC6800_tuner_cfg_cxd2856.tuner_application - 3 < 2) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x40);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x41);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x42);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x4a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x52);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x5a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x2);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x5a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x2);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x9a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x2);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0xda);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x1a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x5a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x5);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x5a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x7);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x5a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x7);
      uVar3 = 0x9a;
    }
    else {
      if (TC6800_tuner_cfg_cxd2856.tuner_application == 1) {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x40);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x41);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x42);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x4a);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x52);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x5a);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x2);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x5a);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x2);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x9a);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x2);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0xda);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x3);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x1a);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x3);
        uVar3 = 0x5a;
      }
      else {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x40);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x41);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x42);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x4a);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x52);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x5a);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x62);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0xa2);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x0);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0xe2);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x1);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x22);
        _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x1);
        uVar3 = 0x62;
      }
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,uVar3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x62);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x5);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0x62);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x5);
      uVar3 = 0xa2;
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,uVar3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x7);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0xa2);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x7);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0xaa);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x7);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0xb2);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xb8,0x7);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xbe,0xb3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xa0,0xc);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x6a);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x1d,0x0,0x1,0x1);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x5);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xc0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x5);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x80);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x45,0x5d);
    cVar7 = '\x04';
    _mt_fe_tn_set_tune_tc6800_cxd2856(0xf37ff,0x32,wait_time);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x14,0x7b);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x12,0x1e);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0xbd,0x1,0x4,0x4);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0xbc,0x3,0x7,0x6);
    _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x53,0xa,0x0,0x7,0x7);
    _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x53,0xd,0x0,0x7,0x7);
    _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x53,0x14,0x1,0x6,0x6);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x5a);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0xc4);
    do {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0xff);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x0);
      cVar7 = cVar7 + -1;
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x0);
      _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x53,0x2,0x1,0x6,0x6);
      _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x53,0x2,0x0,0x6,0x6);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x3a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x6);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x54,&local_34);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x8);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x54,&local_33);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x50,&local_32);
      if (((local_34 - 0x2c < 3) && (local_33 - 0x2c < 3)) && ((byte)(local_32 + 0x3b) < 4)) break;
    } while (cVar7 != '\0');
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0x1);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x12,0xe);
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0xbd,0x0,0x4,0x4);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0xa);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x80);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0xb);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0xc);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0xd);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x80);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0xe);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x53,0xf);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x54,0x0);
    if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 24000) {
      _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x5b,0x2,0x5,0x3);
    }
    else if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 27000) {
      _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x5b,0x6,0x5,0x3);
      _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x4e,0x8,0x1,0x7,0x7);
      _mt_fe_tn_set_tune_tc6800_cxd2856(0x79ac9,0x32,wait_time_01);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x77);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x3a,local_31);
      bVar6 = local_31[0] & 0x3f | 0x40;
      local_31[0] = bVar6;
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x77);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,bVar6);
    }
    if (((uint)TC6800_tuner_cfg_cxd2856.tuner_mode - 1 < 2) && (1 < TC6800_tuner_cfg_cxd2856.tuner_int_lt)
       ) {
      _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x4e,0xf,0x3,0x5,0x4);
      _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x4e,0x10,0x1,0x1,0x1);
      _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x4e,0x11,0x1,0x7,0x4);
      _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(0x4e,0x19,0x0,0x1,0x1);
      _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x46,0x1,0x7,0x7);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2e);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x26);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x26);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x26);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x22);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x42);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x42);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x42);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x42);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x42);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x24);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x34);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x34);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x54);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x64);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x74);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x18);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x18);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x28);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x28);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x38);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x38);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x38);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x38);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x19);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x29);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x29);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x39);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x39);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x1d);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2d);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x3d);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x3a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x5a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x7a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x9b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0xab);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x9f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x8f);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x87);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x7b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0xa4);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x92);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x86);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0xa6);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x9e);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x93);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x8b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x83);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x7b);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x76);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x71);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0xa5);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0xa2);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x97);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x8c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x82);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x77);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0xa3);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x93);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x83);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x99);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x75);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0xa0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x89);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0xa1);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x8c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x20);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x20);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x20);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x20);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x2c);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x14);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x47,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x45,0x1d);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x40,0x1a);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x41,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x60,0x34);
      _mt_fe_tn_set_tune_tc6800_cxd2856(0x79950,0xc8,wait_time_00);
      _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x3e,0x0,0x7,0x7);
    }
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x45,0x5d);
    if (0 < tuner_terr_cable_debug) {
      printk(&.LC20,"_mt_fe_tn_poweron_set_tc6800_cxd2856",0x748);
    }
    _mt_fe_tn_set_reg_bit_tc6800_cxd2856(0x3c,0x1,0x7,0x7);
  }
  else {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x45,0x5d);
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4,0x7f);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0xd8);
  _mt_fe_tn_preset_tc6800_cxd2856();
                    /* Unresolved local var: uint16_t ccval@[???]
                       Unresolved local var: uint16_t ccval_h@[???]
                       Unresolved local var: uint16_t ccval_l@[???]
                       Unresolved local var: uint8_t buf@[???]
                       Unresolved local var: uint8_t idxh@[???]
                       Unresolved local var: uint8_t idxl@[???]
                       Unresolved local var: uint32_t freq_ch@[???]
                       Unresolved local var: uint32_t freq_h@[???]
                       Unresolved local var: uint32_t freq_l@[???] */
  uVar5 = 0;
  _mt_fe_tn_set_RF_front_tc6800_cxd2856(freq_KHz_00);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0xf8);
  _mt_fe_tn_set_Mixer_tc6800_cxd2856(freq_KHz_00,(uint8_t)uVar8);
  _mt_fe_tn_set_LO_tc6800_cxd2856(freq_KHz_00,(uint8_t)uVar8);
  _mt_fe_tn_set_PLL_freq_tc6800_cxd2856();
  _mt_fe_tn_set_BB_tc6800_cxd2856();
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x4,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x0);
  uVar1 = TC6800_tuner_cfg_cxd2856.tuner_freq;
  local_31[0] = 0;
  _mt_fe_tn_get_reg_tc6800_cxd2856(0x3e,local_31);
  bVar6 = local_31[0] & 0x80;
  if ((((uint)TC6800_tuner_cfg_cxd2856.tuner_mode - 1 < 2) && (1 < TC6800_tuner_cfg_cxd2856.tuner_int_lt))
     && ((local_31[0] & 0x80) == 0)) {
    local_31[0] = bVar6;
    if (uVar1 < 0xe8e90) {
      if (uVar1 < 0xd1790) {
        if (uVar1 < 810000) {
          if (uVar1 < 0xb42d0) {
            if (0xa0a4f < uVar1) {
              uVar4 = 80000;
              pcVar6 = 0xb42d0;
              reg_data = 0x4;
              uVar3 = 0x3;
            }
            else if (uVar1 < 0x8f110) {
              if (uVar1 < 0x83590) {
                if (uVar1 < 0x79950) {
                  if (uVar1 < 0x73b90) {
                    if (uVar1 < 0x6c278) {
                      if (uVar1 < 0x664b8) {
                        if (uVar1 < 0x606f8) {
                          if (uVar1 < 0x5a938) {
                            if (uVar1 < 0x56ab8) {
                              if (uVar1 < 0x52c38) {
                                if (uVar1 < 0x518b1) {
                                  if (uVar1 < 0x3b538) {
                                    if (uVar1 < 0x376b8) {
                                      if (uVar1 < 0x33838) {
                                        if (uVar1 < 0x2f9b8) {
                                          if (uVar1 < 0x2bb38) {
                                            if (uVar1 < 0x27cb8) {
                                              if (uVar1 < 0x23e38) {
                                                if (uVar1 < 0x1ffb8) {
                                                  pcVar6 = 0x1b580;
                                                  if (uVar1 < 0x1b581) {
                                                    if (uVar1 < 88000) {
                                                      if (uVar1 < 80000) {
                                                        if (uVar1 < 0x10b94) {
                                                          if (uVar1 < 0xec54) {
                                                            if (uVar1 < 0xcd14) {
                                                              reg_data = 0x1d;
                                                              uVar3 = 0x1d;
                                                              uVar4 = 10000;
                                                              pcVar6 = 0xcd14;
                                                            }
                                                            else {
                                                              uVar4 = 8000;
                                                              pcVar6 = 0xec54;
                                                              reg_data = 0x1d;
                                                              uVar3 = 0x1c;
                                                            }
                                                          }
                                                          else {
                                                            uVar4 = 8000;
                                                            pcVar6 = 0x10b94;
                                                            reg_data = 0x1c;
                                                            uVar3 = 0x1b;
                                                          }
                                                        }
                                                        else {
                                                          uVar4 = 0x2cec;
                                                          pcVar6 = 80000;
                                                          reg_data = 0x1b;
                                                          uVar3 = 0x1a;
                                                        }
                                                      }
                                                      else {
                                                        uVar4 = 8000;
                                                        pcVar6 = 88000;
                                                        reg_data = 0x1a;
                                                        uVar3 = 0x19;
                                                      }
                                                    }
                                                    else {
                                                      reg_data = 0x19;
                                                      uVar4 = 24000;
                                                      uVar3 = 0x19;
                                                    }
                                                  }
                                                  else {
                                                    uVar4 = 16000;
                                                    pcVar6 = 0x1ffb8;
                                                    reg_data = 0x18;
                                                    uVar3 = 0x17;
                                                  }
                                                }
                                                else {
                                                  uVar4 = 16000;
                                                  pcVar6 = 0x23e38;
                                                  reg_data = 0x17;
                                                  uVar3 = 0x16;
                                                }
                                              }
                                              else {
                                                uVar4 = 16000;
                                                pcVar6 = 0x27cb8;
                                                reg_data = 0x16;
                                                uVar3 = 0x15;
                                              }
                                            }
                                            else {
                                              uVar4 = 16000;
                                              pcVar6 = 0x2bb38;
                                              reg_data = 0x15;
                                              uVar3 = 0x14;
                                            }
                                          }
                                          else {
                                            uVar4 = 16000;
                                            pcVar6 = 0x2f9b8;
                                            reg_data = 0x14;
                                            uVar3 = 0x13;
                                          }
                                        }
                                        else {
                                          uVar4 = 16000;
                                          pcVar6 = 0x33838;
                                          reg_data = 0x13;
                                          uVar3 = 0x12;
                                        }
                                      }
                                      else {
                                        uVar4 = 16000;
                                        pcVar6 = 0x376b8;
                                        reg_data = 0x12;
                                        uVar3 = 0x11;
                                      }
                                    }
                                    else {
                                      uVar4 = 16000;
                                      pcVar6 = 0x3b538;
                                      reg_data = 0x11;
                                      uVar3 = 0x10;
                                    }
                                  }
                                  else {
                                    uVar4 = 91000;
                                    pcVar6 = 0x518b0;
                                    reg_data = 0x10;
                                    uVar3 = 0xf;
                                  }
                                }
                                else {
                                  reg_data = 0xe;
                                  pcVar6 = 0x52c38;
                                  uVar3 = 0xe;
                                  uVar4 = 5000;
                                }
                              }
                              else {
                                uVar4 = 16000;
                                pcVar6 = 0x56ab8;
                                reg_data = 0xe;
                                uVar3 = 0xd;
                              }
                            }
                            else {
                              uVar4 = 16000;
                              reg_data = 0xd;
                              uVar3 = 0xc;
                              pcVar6 = 0x5a938;
                            }
                          }
                          else {
                            uVar4 = 24000;
                            pcVar6 = 0x606f8;
                            reg_data = 0xc;
                            uVar3 = 0xb;
                          }
                        }
                        else {
                          uVar4 = 24000;
                          pcVar6 = 0x664b8;
                          reg_data = 0xb;
                          uVar3 = 0xa;
                        }
                      }
                      else {
                        uVar4 = 24000;
                        pcVar6 = 0x6c278;
                        reg_data = 0xa;
                        uVar3 = 0x9;
                      }
                    }
                    else {
                      uVar4 = 31000;
                      pcVar6 = 0x73b90;
                      reg_data = 0x9;
                      uVar3 = 0x8;
                    }
                  }
                  else {
                    uVar4 = 24000;
                    pcVar6 = 0x79950;
                    reg_data = 0x8;
                    uVar3 = 0x7;
                  }
                }
                else {
                  uVar4 = 40000;
                  pcVar6 = 0x83590;
                  reg_data = 0x7;
                  uVar3 = 0x6;
                }
              }
              else {
                uVar4 = 48000;
                pcVar6 = 0x8f110;
                reg_data = 0x6;
                uVar3 = 0x5;
              }
            }
            else {
              uVar4 = 72000;
              pcVar6 = 0xa0a50;
              reg_data = 0x5;
              uVar3 = 0x4;
            }
          }
          else {
            uVar4 = 72000;
            pcVar6 = 810000;
            reg_data = 0x3;
            uVar3 = 0x2;
          }
        }
        else {
          uVar4 = 48000;
          pcVar6 = 0xd1790;
          reg_data = 0x2;
          uVar3 = 0x1;
        }
      }
      else {
        uVar3 = 0x0;
        uVar4 = 96000;
        pcVar6 = 0xe8e90;
        reg_data = 0x1;
      }
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x48,uVar3);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x48,local_31);
      uVar9 = (uint)local_31[0];
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x49,local_31);
      uVar5 = (uint)local_31[0];
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x48,reg_data);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x48,local_31);
      bVar6 = local_31[0];
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x49,local_31);
      uVar5 = (uVar9 & 0x80) * 2 + uVar5;
LAB_0008c710:
      uVar9 = (bVar6 & 0x80) * 2 + (uint)local_31[0];
      if (uVar9 <= uVar5) {
        uVar9 = (pcVar6 - uVar1) * (uVar5 - uVar9);
        goto LAB_0008d814;
      }
      iVar2 = __aeabi_uidiv((pcVar6 - uVar1) * (uVar9 - uVar5),uVar4);
      uVar5 = uVar5 + iVar2;
    }
    else {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x48,0x0);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x48,local_31);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x49,local_31);
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x48,0x0);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x48,local_31);
      bVar6 = local_31[0];
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x49,local_31);
      uVar9 = 0;
      if (uVar1 < 0xf6950) {
        pcVar6 = 0xf6950;
        uVar4 = 56000;
        uVar5 = uVar9;
        goto LAB_0008c710;
      }
      uVar4 = 56000;
LAB_0008d814:
      iVar2 = __aeabi_uidiv(uVar9,uVar4);
      uVar5 = uVar5 + iVar2;
    }
    uVar5 = uVar5 & 0xffff;
    local_31[0] = (byte)((uVar5 << 0x17) >> 0x1f) | 4;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x80,local_31[0]);
    local_31[0] = (byte)uVar5;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x81,local_31[0]);
    local_31[0] = ~((byte)~(byte)((uVar5 << 0x19) >> 0x18) >> 1);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x82,local_31[0]);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7e,0x1a);
    _mt_fe_tn_get_reg_tc6800_cxd2856(0x7f,local_31);
    local_31[0] = local_31[0] | 0x10;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x7f,local_31[0]);
    bVar6 = local_31[0];
  }
  local_31[0] = bVar6;
  _mt_fe_tn_set_DAC_tc6800_cxd2856(freq_KHz_00);
  if ((TC6800_tuner_cfg_cxd2856.tuner_application & 0xfd) == 1) {
    uVar3 = 0x15;
  }
  else {
    uVar3 = 0x5;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xc9,uVar3);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x40,0x1a);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x41,0x0);
  if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 24000) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x44,0x22);
  }
  else if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 27000) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x44,0x2a);
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x60,0x34);
  if (((uint)TC6800_tuner_cfg_cxd2856.tuner_mode - 1 < 2) && (1 < TC6800_tuner_cfg_cxd2856.tuner_int_lt))
  {
    _mt_fe_tn_get_reg_tc6800_cxd2856(0x9a,&local_36);
    local_36 = local_36 | 0x10;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x9a,local_36);
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x4);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xc2,0x1);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x0,0x1);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x0,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xc2,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x5,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x0);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
  if ((uint)TC6800_tuner_cfg_cxd2856.tuner_mode - 1 < 2) {
    if (TC6800_tuner_cfg_cxd2856.tuner_int_lt < 2) goto LAB_0008c7a0;
    local_36 = local_36 & 0xef;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x9a,local_36);
    if (1 < (uint)TC6800_tuner_cfg_cxd2856.tuner_mode - 1) goto LAB_0008c35c;
    if (TC6800_tuner_cfg_cxd2856.tuner_int_lt == 0x2) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0xfd,0x1a);
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x8b,&local_35);
      local_35 = local_35 & 0x77;
      bVar6 = local_35;
      if (TC6800_tuner_cfg_cxd2856.tuner_custom_cfg == 1) {
        bVar6 = 0xaa;
      }
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x8b,bVar6);
      if ((ushort)(TC6800_tuner_cfg_cxd2856.tuner_mode - 1) < 2) goto LAB_0008c7a0;
    }
    else {
LAB_0008c7a0:
      _mt_fe_tn_get_reg_tc6800_cxd2856(0x9a,&local_37);
      local_37 = local_37 & 0xf;
      if (local_37 < 10) {
        if (local_37 < 4) {
          _mt_fe_tn_set_reg_tc6800_cxd2856(0x1c,0x43);
        }
      }
      else {
        _mt_fe_tn_set_reg_tc6800_cxd2856(0x1c,0x93);
      }
    }
    if (TC6800_tuner_cfg_cxd2856.tuner_mode != 2) goto LAB_0008c35c;
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xd,0xcc);
  }
  else {
LAB_0008c35c:
    _mt_fe_tn_set_reg_tc6800_cxd2856(0xd,0xc4);
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x3d,0xfe);
  _mt_fe_tn_get_reg_tc6800_cxd2856(0x4a,&local_37);
  uVar5 = (uint)local_37;
  local_37 = (byte)(uVar5 & 0xf);
  _mt_fe_tn_get_reg_tc6800_cxd2856(0x4b,&local_37);
  uVar9 = (uint)local_37;
  _mt_fe_tn_get_reg_tc6800_cxd2856(0x4c,&local_37);
  uVar9 = uVar9 + (uVar5 & 0xf) * 0x100 >> (((uint)local_37 << 0x19) >> 0x1e);
  local_37 = (byte)(((uint)local_37 << 0x19) >> 0x1e);
  uVar5 = uVar9 * 8;
  if (TC6800_tuner_cfg_cxd2856.tuner_crystal == 27000) {
    uVar5 = (uVar9 * 0xd8) / 0x18;
  }
  if (((uVar5 * 1000 - freq_KHz_00 < 20001) || (freq_KHz_00 + uVar5 * -1000 < 20001)) ||
     ((uVar5 * 1000 + freq_KHz_00 * -3 < 20001 || (freq_KHz_00 * 3 + uVar5 * -1000 < 20001)))) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x10,0x50);
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x66,0x48);
  _mt_fe_tn_set_reg_tc6800_cxd2856(0xb0,0xb);
  uVar3 = TC6800_tuner_cfg_cxd2856.tuner_application;
  if ((uint)TC6800_tuner_cfg_cxd2856.tuner_application - 3 < 2) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x11);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x18);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x12);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x6a);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x15);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x16);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x17);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x35);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x18);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x1);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x19);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x18);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x5);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x8);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x6);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x4e);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x9);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xa);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xb);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x27);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xc);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xd);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x8);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xae);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2c);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x9);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x8);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xee);
LAB_0008d1cc:
    if (TC6800_tuner_cfg_cxd2856.tuner_application == 0x3) {
      _mt_fe_tn_set_reg_tc6800_cxd2856(0x60,0xb7);
      goto LAB_0008c440;
    }
  }
  else if (TC6800_tuner_cfg_cxd2856.tuner_application == 1) {
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x11);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x12);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0xb);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x15);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x16);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x17);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x5);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x18);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x19);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x7f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x5);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x6);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0x9);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xa);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xb);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,uVar3);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xc);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x0);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x39,0xd);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x3a,0x7f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x8c);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2c);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x20);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x2f);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0x2);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4e,0x29);
    _mt_fe_tn_set_reg_tc6800_cxd2856(0x4f,0xcc);
    goto LAB_0008d1cc;
  }
  _mt_fe_tn_set_reg_tc6800_cxd2856(0x60,0x34);
LAB_0008c440:
  if (0 < tuner_terr_cable_debug) {
    printk(&.LC21,"mt_fe_tn_set_freq_tc6800_cxd2856",0xafe);
  }
  return;
}
