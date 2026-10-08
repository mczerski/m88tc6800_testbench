#pragma once
#include "gtm_hardware_fe.ko.h"

#define GTM_Tuner_t void
extern struct _MT_FE_TN_Device_Settings_TC6800 TC6800_tuner_cfg_cxd2856;
uint32_t _mt_fe_tn_set_reg_bit_tc6800_cxd2856(uint8_t reg_addr,uint8_t data,
                                              uint8_t high_bit,uint8_t low_bit);
uint32_t _mt_fe_tn_set_reg_bit_expand_tc6800_cxd2856(uint8_t reg_addr_expand,uint8_t reg_addr,
                                                     uint8_t reg_data,uint8_t high_bit,
                                                     uint8_t low_bit);
void _mt_fe_tn_preset_tc6800_cxd2856(void);
void _mt_fe_tn_set_RF_front_tc6800_cxd2856(uint32_t freq_KHz);
void _mt_fe_tn_set_Mixer_tc6800_cxd2856(uint32_t freq_KHz,uint8_t mixer_sel);
void _mt_fe_tn_set_LO_tc6800_cxd2856(uint32_t freq_KHz,uint8_t mixer_sel);
void _mt_fe_tn_set_PLL_freq_tc6800_cxd2856(void);
void _mt_fe_tn_set_BB_tc6800_cxd2856(void);
void _mt_fe_tn_set_DAC_tc6800_cxd2856(uint32_t freq_KHz);
void mt_fe_tn_set_freq_tc6800_cxd2856(uint32_t freq_KHz);
void _mt_fe_tn_set_tune_tc6800_cxd2856(uint32_t freq_KHz,uint8_t mixer_sel,uint32_t wait_time);
uint32_t TC6800_GetRFStrength(GTM_Tuner_t *pTuner,int32_t *pRfStrength);
