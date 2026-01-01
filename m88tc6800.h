#pragma once
#include <stdbool.h>

#define u8 uint8_t
#define u32 uint32_t

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

extern struct m88tc6800_priv priv;
void m88tc6800_preset(struct m88tc6800_priv *priv);
void m88tc6800_set_rf_frontend(struct m88tc6800_priv *priv, u32 freq_khz);
void m88tc6800_set_mixer(struct m88tc6800_priv *priv, u32 freq_khz, u8 mixer_type);
void m88tc6800_set_lo(struct m88tc6800_priv *priv, u32 freq_khz, u8 mixer_type);
void m88tc6800_set_pll(struct m88tc6800_priv *priv);
void m88tc6800_set_bandwidth(struct m88tc6800_priv *priv);
void m88tc6800_set_dac(struct m88tc6800_priv *priv, uint32_t freq_khz);
int m88tc6800_set_freq(struct m88tc6800_priv *priv, u32 freq_khz);
void m88tc6800_set_tune(struct m88tc6800_priv *priv, uint32_t freq_KHz, uint8_t mixer_sel, uint32_t wait_time);
