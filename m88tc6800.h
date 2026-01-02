#pragma once
#include <stdbool.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s32 int32_t

struct m88tc6800_config {
	u8 addr;
	u32 xtal;
	u8 xtal_cap;
	u8 mode;
	u8 lt;
	u8 im;
	u8 custom_cfg;
	u8 harmonic_imp;
	u8 dac_gain;
	u32 dac;
};

struct m88tc6800_priv {
	struct m88tc6800_config config;
//	struct i2c_adapter *i2c;
	bool mcu_status;
	u32 frequency_hz;
	u32 bandwidth_hz;
	u32 ldiv;
	u32 fvco_tg;
};

extern struct m88tc6800_priv priv;
void m88tc6800_preset(struct m88tc6800_priv *priv);
void m88tc6800_set_rf_frontend(struct m88tc6800_priv *priv, u32 freq_khz);
void m88tc6800_set_mixer(struct m88tc6800_priv *priv, u32 freq_khz, u8 mixer_type);
void m88tc6800_set_lo(struct m88tc6800_priv *priv, u32 freq_khz, u8 mixer_type);
void m88tc6800_set_pll(struct m88tc6800_priv *priv);
void m88tc6800_set_bandwidth(struct m88tc6800_priv *priv, u32 bandwidth_hz);
void m88tc6800_set_dac(struct m88tc6800_priv *priv, u32 freq_khz, u32 bandwidth_hz);
int m88tc6800_set_freq(struct m88tc6800_priv *priv, u32 freq_khz, u32 bandwidth_hz);
void m88tc6800_set_tune(struct m88tc6800_priv *priv, u32 freq_KHz, u32 bandwidth_hz, u8 mixer_sel, u32 wait_time_ms);
int m88tc6800_get_rf_strength(struct m88tc6800_priv *priv, u16 *strength);
