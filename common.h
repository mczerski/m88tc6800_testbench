#include "gtm_hardware_fe.ko.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define u8 uint8_t
#define u32 uint32_t

void __gnu_mcount_nc(void) {}
unsigned __aeabi_uidivmod(unsigned numerator, unsigned denominator) { return numerator % denominator; }
unsigned __aeabi_uidiv(unsigned numerator, unsigned denominator) { return numerator / denominator; }
void printk(void);

struct _MT_FE_TN_Device_Settings_TC6800 TC6800_tuner_cfg_cxd2856;
uint8_t tuner_terr_cable_debug = 0;

uint32_t i2c_log[1000];
uint32_t expected_i2c_op = 0;
uint32_t actual_i2c_op = 0;
uint8_t i2c_reg[256];

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

void init() {
  TC6800_tuner_cfg_cxd2856.tuner_mode = 0x0;
  TC6800_tuner_cfg_cxd2856.tuner_mcu_status = 0x0;
  TC6800_tuner_cfg_cxd2856.tuner_application = 0x0;
  TC6800_tuner_cfg_cxd2856.tuner_custom_cfg = 0;
  TC6800_tuner_cfg_cxd2856.tuner_signal_delay_en = 0x0;
  TC6800_tuner_cfg_cxd2856.tuner_signal_delay_ns = 0;
  TC6800_tuner_cfg_cxd2856.tuner_mixer_type = 0;
  TC6800_tuner_cfg_cxd2856.tuner_gpio_out = 0x0;
  TC6800_tuner_cfg_cxd2856.tuner_time = 0x112d838;
  TC6800_tuner_cfg_cxd2856.tuner_int_lt = 0x2;
  TC6800_tuner_cfg_cxd2856.tuner_dac_gain = 0x2;
  TC6800_tuner_cfg_cxd2856.tuner_int_im = 0x2;
  TC6800_tuner_cfg_cxd2856.tuner_dac = 0x11da;
  TC6800_tuner_cfg_cxd2856.tuner_crystal = 27000;
  TC6800_tuner_cfg_cxd2856.tuner_crystal_cap = 0x18;
  TC6800_tuner_cfg_cxd2856.tuner_clock_out = 0x1;
  TC6800_tuner_cfg_cxd2856.tuner_harmonic_imp = 0x1;
  TC6800_tuner_cfg_cxd2856.tuner_version = 0x7a;
  TC6800_tuner_cfg_cxd2856.tuner_fw_version = 0xc;
  expected_i2c_op = 0;
  actual_i2c_op = 0;
}

void finish() {
    if (expected_i2c_op != actual_i2c_op) {
        printf("expected ops: %d, actual ops: %d\n", expected_i2c_op, actual_i2c_op);
        exit(0);
    }
}

struct m88tc6800_config {
	u8 addr;
	u32 xtal;
	u8 xtal_cap;
};

struct m88tc6800_priv {
	struct m88tc6800_config config;
//	struct i2c_adapter *i2c;
	bool mcu_status;
	uint32_t ldiv;
	uint32_t fvco_tg;
//	uint32_t freq_khz;
	uint32_t bandwidth_hz;
//	u8 locked;
//	enum fe_delivery_system delivery_system;
//	u32 rf_frequency_hz;
//	u32 if_frequency_hz;
//	u32 bandwidth_hz;
//	u32 lpf_hz;
};

struct m88tc6800_priv priv;

static int m88tc6800_write_reg(struct m88tc6800_priv *priv, u8 reg, u8 val)
{
    uint32_t actual_op = ('w' << 24) + (reg << 8) + val;
    uint32_t expected_op = i2c_log[actual_i2c_op];
    if (actual_op != expected_op) {
        printf("op: %d, actual: %08x, expected: %08x\n", actual_i2c_op, actual_op, expected_op);
        exit(0);
    }
    actual_i2c_op++;
    return 0;
}

static int m88tc6800_read_reg(struct m88tc6800_priv *priv, u8 reg, u8 *val)
{
    *val = i2c_reg[reg];
    uint32_t actual_op = ('r' << 24) + (reg << 8) + *val;
    uint32_t expected_op = i2c_log[actual_i2c_op];
    if (actual_op != expected_op) {
        printf("op: %d, actual: %08x, expected: %08x\n", actual_i2c_op, actual_op, expected_op);
        exit(0);
    }
    actual_i2c_op++;
    return 0;
}

static int m88tc6800_set_reg_bits(struct m88tc6800_priv *priv, u8 reg, u8 val, u8 begin_bit, u8 end_bit)
{
	u8 val_mask = ((1 << (end_bit - begin_bit + 1)) - 1) << begin_bit;
	u8 reg_data;
	int ret;

	ret = m88tc6800_read_reg(priv, reg, &reg_data);
	if (ret)
		return ret;

	reg_data &= ~val_mask;
	val = (val << begin_bit) & val_mask;
	reg_data |= val;

  ret = m88tc6800_write_reg(priv, reg, reg_data);
  return ret;
}

uint32_t m88tc6800_expand_reg_bits(struct m88tc6800_priv *priv, u8 reg_expand, u8 reg, u8 val, u8 start_bit, u8 end_bit)
{
  byte reg_data_00;
  uint8_t reg_addr_00 = reg_expand;
  uint8_t reg_data_01 = reg;
  int extraout_r2 = val;
  uint extraout_r3 = end_bit;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte local_31 [5];
  
  uVar2 = (uint)start_bit;
  local_31[0] = 0;
  uVar1 = uVar2;
  uVar3 = extraout_r3;
  if (uVar2 <= extraout_r3) {
    uVar1 = extraout_r3;
    uVar3 = uVar2;
  }
  uVar3 = (uVar3 + 7) - uVar1;
  m88tc6800_write_reg(priv, reg_addr_00,reg_data_01);
  m88tc6800_read_reg(priv, reg_addr_00 + 0x1,local_31);
  reg_data_00 = local_31[0] & ~(byte)((int)(0xff << (uVar3 & 0xff) & 0xffU) >> (7 - uVar1 & 0xff)) |
                (byte)((int)(extraout_r2 << (uVar3 & 0xff) & 0xffU) >> (7 - uVar1 & 0xff));
  local_31[0] = reg_data_00;
  m88tc6800_write_reg(priv, reg_addr_00,reg_data_01);
  m88tc6800_write_reg(priv, reg_addr_00 + 0x1,reg_data_00);
  return 0;
}
