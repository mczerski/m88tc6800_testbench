#include "m88tc6800_priv.h"

//TODO: remove application (always application == 0)

int m88tc6800_set_reg_bits(struct m88tc6800_priv *priv, u8 reg, u8 val, u8 begin_bit, u8 end_bit)
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

void m88tc6800_preset(struct m88tc6800_priv *priv)
{
    u8 reg_data;

    if (0 < priv->config.mode && priv->config.mode <= 2) {
        m88tc6800_write_reg(priv, 0x0b, 0x7d);
    }
    else {
        m88tc6800_write_reg(priv, 0x0b, 0x6d);
    }
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

/* Refactored from Ghidra decompilation of _mt_fe_tn_set_RF_front_tc6800_cxd2856.
 *
 * Variable name mapping from decompilation:
 *   extraout_r0  -> freq_KHz     (function argument, Ghidra artefact)
 *   local_21[0]  -> lna_val      (LNA/attenuator state byte for reg 0x8b)
 *   bVar3        -> lna_val      (copy of lna_val before custom_cfg override)
 *   uVar4        -> reg_val      (scratch byte for register values)
 *   bVar1        -> in_610_band  (freq in [610000..623999])
 *   bVar2        -> in_480_band  (freq in [480000..491999])
 *
 * Structure overview:
 *
 * Phase 1 — IM mode setup (regs 0x88/0x89/0x8a/0x39/0x3a + lna_val):
 *   Selects oscillator and mixer settings based on tuner_int_im.
 *   For int_im == 2, the freq/application condition also chooses between
 *   two sets of regs 0x39/0x3a and two lna_val defaults (0x55 or 0x11).
 *
 * Phase 2 — LNA gain control (regs 0x8b, 0xfd):
 *   fd_val = 0x12 when mode in {1,2} AND int_lt >= 2 (the int_lt path);
 *   fd_val = 0x1a otherwise (the direct path).
 *   For the int_lt path, lna_val is overridden:
 *     int_im == 2 → lna_val = reg_0x8b | 0x88
 *     other       → lna_val = 0xaa
 *   custom_cfg == 1 always forces lna_val = 0xaa regardless.
 *
 * Phase 3 — RF band filter (regs 0x7f/0x92/0x87/0x90):
 *   Selects band-pass filter and gain block settings by frequency.
 *   This selection is identical for both fd_val paths.
 *
 * Phase 4 — Application-specific tail (regs 0xaa/0xa9/0x98/0x99/0x26/0x94/...):
 *   Configures harmonic rejection and spur optimisation based on
 *   tuner_application, tuner_harmonic_imp, and freq.
 */
//struct m88tc6800_priv {
//    uint32_t tuner_int_im;        /* image rejection mode: 0=low-IF, 1=mid-IF, 2=high-IF */
//    uint32_t tuner_int_lt;        /* loop-through enable threshold                        */
//    uint32_t tuner_mode;          /* tuner mode (1/2 = cable/terrestrial, others = other) */
//    uint32_t tuner_application;   /* 0=auto, 1=DVB-T, 3=ISDB-T, 4=DVB-C                 */
//    uint32_t tuner_custom_cfg;    /* 1 = override LNA state to 0xaa                      */
//    uint32_t tuner_harmonic_imp;  /* 1 = harmonic improvement mode enabled               */
//};

void m88tc6800_set_rf_frontend(struct m88tc6800_priv *priv, uint32_t freq_KHz)
{
    uint8_t lna_val;
    uint8_t reg_val;
    uint32_t application = 0;

    /* ------------------------------------------------------------------
     * Phase 1: oscillator / mixer register setup and lna_val default.
     *
     * int_im == 0 / 1: shared regs 0x39=0x69, 0x3a=0x12 and lna_val=0x22.
     *   The only difference between 0 and 1 is the value written to 0x88/0x8a.
     *
     * int_im == 2: regs 0x88/0x89/0x8a are fixed (0x2b/0x2b/0xab).
     *   The freq + application condition selects between two 0x3a values
     *   and sets the lna_val default to 0x55 (low-freq non-DVB-T) or 0x11.
     * ------------------------------------------------------------------ */
    if (priv->config.int_im == 0) {
        m88tc6800_write_reg(priv, 0x88, 0x27);
        m88tc6800_write_reg(priv, 0x89, 0x2b);
        m88tc6800_write_reg(priv, 0x8a, 0x67);
        lna_val = 0x22;
        m88tc6800_write_reg(priv, 0x39, 0x69);
        m88tc6800_write_reg(priv, 0x3a, 0x12);
    } else if (priv->config.int_im == 1) {
        m88tc6800_write_reg(priv, 0x88, 0x1b);
        m88tc6800_write_reg(priv, 0x89, 0x2b);
        m88tc6800_write_reg(priv, 0x8a, 0x1b);
        lna_val = 0x22;
        m88tc6800_write_reg(priv, 0x39, 0x69);
        m88tc6800_write_reg(priv, 0x3a, 0x12);
    } else {
        /* int_im == 2 */
        m88tc6800_write_reg(priv, 0x88, 0x2b);
        m88tc6800_write_reg(priv, 0x89, 0x2b);
        m88tc6800_write_reg(priv, 0x8a, 0xab);
        if (freq_KHz < 602001U && application != 1U) {
            lna_val = 0x55;
            m88tc6800_write_reg(priv, 0x39, 0x69);
            m88tc6800_write_reg(priv, 0x3a, 0x2d);
        } else {
            lna_val = 0x11;
            m88tc6800_write_reg(priv, 0x39, 0x69);
            m88tc6800_write_reg(priv, 0x3a, 0x09);
        }
    }

    /* ------------------------------------------------------------------
     * Phase 2: LNA/attenuator state register (0x8b) and loop-through
     * divider register (0xfd).
     *
     * When mode is 1 or 2 (tuner_mode - 1 unsigned <= 1) AND int_lt >= 2,
     * the hardware can read back the current 0x8b state and augment it:
     *   int_im == 2 → lna_val = current_0x8b | 0x88
     *   other       → lna_val = 0xaa
     * and fd_val = 0x12 (loop-through enabled).
     * Otherwise lna_val keeps its phase-1 default and fd_val = 0x1a.
     *
     * custom_cfg == 1 forces lna_val = 0xaa unconditionally after either path.
     * ------------------------------------------------------------------ */
    bool use_lt_path = ((priv->config.mode - 1U) <= 1U) && (priv->config.int_lt >= 2U);
    uint8_t fd_val;

    if (use_lt_path) {
        if (priv->config.int_im == 2U) {
            m88tc6800_read_reg(priv, 0x8b, &reg_val);
            lna_val = reg_val | 0x88U;
        } else {
            lna_val = 0xaa;
        }
        fd_val = 0x12;
    } else {
        /* lna_val already set from phase 1 */
        fd_val = 0x1a;
    }

    if (priv->config.custom_cfg == 1U)
        lna_val = 0xaa;

    m88tc6800_write_reg(priv, 0x8b, lna_val);
    m88tc6800_write_reg(priv, 0xfd, fd_val);

    /* ------------------------------------------------------------------
     * Phase 3: RF band-pass filter and gain block selection.
     *
     * The frequency boundaries and register values are identical regardless
     * of which path was taken above. reg 0x90 value differs only at the
     * top end: 0x49 for freq <= 451000 kHz, 0x4a above.
     *
     * Boundary summary (kHz):
     *   <= 112000 : low band  — 0x7f=0x08, 0x92=0x8c (0xac for DVB-T), 0x90=0x49
     *   <= 334000 : mid-low   — 0x7f=0x04, 0x92=0x8c,                   0x90=0x49
     *   <= 451000 : mid-high  — 0x7f=0x00, 0x92=0x8c,                   0x90=0x49
     *   >  451000 : high band — 0x7f=0x00, 0x92=0x8c,                   0x90=0x4a
     * ------------------------------------------------------------------ */
    if (freq_KHz <= 112000U) {
        m88tc6800_write_reg(priv, 0x7f, 0x08);
        m88tc6800_write_reg(priv, 0x92,
                    application == 1U ? 0xac : 0x8c);
        m88tc6800_write_reg(priv, 0x87, 0xf0);
        m88tc6800_write_reg(priv, 0x90, 0x49);
    } else if (freq_KHz <= 334000U) {
        m88tc6800_write_reg(priv, 0x7f, 0x04);
        m88tc6800_write_reg(priv, 0x92, 0x8c);
        m88tc6800_write_reg(priv, 0x87, 0xf0);
        m88tc6800_write_reg(priv, 0x90, 0x49);
    } else if (freq_KHz <= 451000U) {
        m88tc6800_write_reg(priv, 0x7f, 0x00);
        m88tc6800_write_reg(priv, 0x92, 0x8c);
        m88tc6800_write_reg(priv, 0x87, 0xf0);
        m88tc6800_write_reg(priv, 0x90, 0x49);
    } else {
        m88tc6800_write_reg(priv, 0x7f, 0x00);
        m88tc6800_write_reg(priv, 0x92, 0x8c);
        m88tc6800_write_reg(priv, 0x87, 0xf0);
        m88tc6800_write_reg(priv, 0x90, 0x4a);
    }

    /* ------------------------------------------------------------------
     * Phase 4: application-specific AGC, harmonic rejection, and spur
     * optimisation register programming.
     * ------------------------------------------------------------------ */
    m88tc6800_write_reg(priv, 0xaa,
                application == 0U ? 0x84 : 0x74);
    m88tc6800_write_reg(priv, 0xa9, 0xf6);

    /* ---- ISDB-T / DVB-C  (tuner_application 3 or 4) ---- */
    if ((application - 3U) < 2U) {
        m88tc6800_write_reg(priv, 0x98, 0xf7);
        m88tc6800_write_reg(priv, 0x99, 0xa5);
        m88tc6800_write_reg(priv, 0x26, 0x14);

        if (priv->config.harmonic_imp != 1U)
            return;

        if (freq_KHz > 334000U) {
            if (freq_KHz < 474001U) {
                m88tc6800_write_reg(priv, 0x94, 0x29);
                return;
            }
            if (freq_KHz < 858001U) {
                m88tc6800_write_reg(priv, 0x94, 0x15);
                return;
            }
        }
        m88tc6800_write_reg(priv, 0x94, 0x01);
        return;
    }

    /* ---- DVB-T (tuner_application == 1) ---- */
    if (application == 1U) {
        m88tc6800_write_reg(priv, 0x98, 0xf5);
        m88tc6800_write_reg(priv, 0x99, 0x94);
        m88tc6800_write_reg(priv, 0x26, 0x14);

        if (priv->config.harmonic_imp == 1U) {
            /* Select reg 0x94 by frequency band */
            if (freq_KHz < 334001U) {
                m88tc6800_write_reg(priv, 0x94, 0x01);
            } else if (freq_KHz < 474001U) {
                m88tc6800_write_reg(priv, 0x94, 0x29);
            } else if (freq_KHz < 858001U) {
                m88tc6800_write_reg(priv, 0x94, 0x15);
            } else {
                m88tc6800_write_reg(priv, 0x94, 0x01);
            }

            /* Select reg 0x3a by frequency:
             * 0x0b for low (< 112001) and high (>= 334001) bands,
             * 0x09 for the mid band [112001..334000].              */
            m88tc6800_write_reg(priv, 0x39, 0x13);
            m88tc6800_write_reg(priv, 0x3a,
                        freq_KHz < 112001U ? 0x0b : 0x09);
        } else {
            /* harmonic_imp == 0: no reg 0x94 write.
             * Same 0x3a selection: 0x0b outside [112001..334000],
             * 0x09 inside.                                         */
            m88tc6800_write_reg(priv, 0x39, 0x13);
            m88tc6800_write_reg(priv, 0x3a,
                        (freq_KHz < 112001U || freq_KHz > 334000U)
                        ? 0x0b : 0x09);
        }
        return;
    }

    /* ---- All other applications (0, 2, …) ---- */
    m88tc6800_write_reg(priv, 0x98, 0xf8);
    m88tc6800_write_reg(priv, 0x99,
                (freq_KHz - 700001U) < 200000U ? 0xa5 : 0xb6);
    m88tc6800_write_reg(priv, 0x26, 0x11);

    if (priv->config.harmonic_imp != 1U)
        return;

    /* Unsigned subtraction range checks (compiler idiom):
     * (x - base) < width  is true for x in [base .. base+width-1]
     * and wraps to a large value for x < base, so it also acts as x >= base. */
    bool in_610_band = (freq_KHz - 610000U) < 14001U;  /* [610000..623999] kHz */
    bool in_480_band = (freq_KHz - 480000U) < 12001U;  /* [480000..491999] kHz */

    if (in_610_band || in_480_band) {
        /* Spur region: attenuate harmonic. The inner condition in the
         * original C is provably always false here (it requires both
         * !in_480_band and !in_610_band simultaneously, which contradicts
         * entering this branch), so the 0x3a=0x01 path is unreachable.  */
        m88tc6800_write_reg(priv, 0x94, 0x15);
    } else if ((freq_KHz - 366000U) < 8001U) {         /* [366000..373999] kHz */
        m88tc6800_write_reg(priv, 0x94, 0x29);
    } else {
        m88tc6800_write_reg(priv, 0x94, 0x01);
        if ((freq_KHz - 800000U) > 20000U) {           /* outside [800000..820000] */
            /* Harmonic improvement with 0x3a=0x01 (stronger filter) */
            m88tc6800_write_reg(priv, 0x39, 0x0e);
            m88tc6800_write_reg(priv, 0x3a, 0x04);
            m88tc6800_write_reg(priv, 0x39, 0x0f);
            m88tc6800_write_reg(priv, 0x3a, 0x04);
            m88tc6800_write_reg(priv, 0x39, 0x10);
            m88tc6800_write_reg(priv, 0x3a, 0x01);
            return;
        }
    }

    /* Default harmonic improvement filter coefficients (0x3a=0x02) */
    m88tc6800_write_reg(priv, 0x39, 0x0e);
    m88tc6800_write_reg(priv, 0x3a, 0x04);
    m88tc6800_write_reg(priv, 0x39, 0x0f);
    m88tc6800_write_reg(priv, 0x3a, 0x04);
    m88tc6800_write_reg(priv, 0x39, 0x10);
    m88tc6800_write_reg(priv, 0x3a, 0x02);
}

/* ------------------------------------------------------------------
 * Mixer path selection (mixer_sel / uVar8).
 *
 * If tuner_mixer_type is explicitly set to 1, 2, or 3, use it
 * directly.  Otherwise auto-select based on frequency and
 * spur-avoidance policy.
 * ------------------------------------------------------------------ */
u8 m88tc6800_get_mixer_type(struct m88tc6800_priv *priv, u32 freq_khz)
{
    if (freq_khz <= 334000) {
        return 2;
    }
    if (priv->config.harmonic_imp == 1) {
        if ((freq_khz >= 480000 && freq_khz <= 492000) ||
               (freq_khz >= 610000 && freq_khz <= 624000) ||
               (freq_khz >= 800000 && freq_khz <= 820000) ||
               (freq_khz >= 366000 && freq_khz <= 374000)) {
            return 3;
        }
        return 1;
    }
    else {
        return 1;
    }
}

/* Refactored from Ghidra decompilation of _mt_fe_tn_set_Mixer_tc6800_cxd2856.
 *
 * Variable name mapping from decompilation:
 *   extraout_r0  -> freq_KHz   (function argument, Ghidra artefact)
 *   extraout_r1  -> mixer_sel  (function argument, Ghidra artefact)
 *   iVar2        -> band_sel   (value written to reg 0x0b bit field;
 *                               equals mixer_sel for sel==2 or sel==3,
 *                               clamped to 1 for all other values)
 *   uVar1        -> reg_val    (scratch byte for register values)
 *
 * Structure overview:
 *
 * Reg 0x2f — mixer band register:
 *   When mixer_sel == 2 AND freq > 124999 kHz, a band-specific value is
 *   written based on the frequency sub-band.  In every other case (including
 *   mixer_sel == 2 with freq <= 124999) the register is cleared to 0x00.
 *
 * Reg 0x0b bits [1:0] — band select:
 *   mixer_sel 2 or 3 is passed through directly.
 *   Any other value is normalised to 1.
 *
 * Reg 0x32 — mixer tuning:
 *   Set to 0x04 when freq is in [330000..400000] kHz, 0x00 otherwise.
 *   (Unsigned subtraction: (freq - 330000) < 70001 covers that range.)
 */

void m88tc6800_set_mixer(struct m88tc6800_priv *priv, uint32_t freq_KHz, uint8_t mixer_sel)
{
    /* Normalise mixer_sel to the value expected by the reg 0x0b bit field.
     * Values 2 and 3 pass through; everything else is treated as 1.       */
    uint8_t band_sel = (mixer_sel == 2U || mixer_sel == 3U) ? mixer_sel : 1U;

    /* ------------------------------------------------------------------
     * Reg 0x2f: mixer sub-band selection.
     *
     * Only mixer_sel == 2 with freq above 124999 kHz uses a non-zero
     * value; the four sub-bands map to an ascending sequence of codes.
     * All other conditions (including mixer_sel == 2 at low frequency)
     * write 0x00 to disable the sub-band override.
     * ------------------------------------------------------------------ */
    if (mixer_sel == 2U && freq_KHz > 124999U) {
        uint8_t band_code;

        if      (freq_KHz < 167000U) band_code = 0x10;
        else if (freq_KHz < 250000U) band_code = 0x21;
        else if (freq_KHz < 335000U) band_code = 0x32;
        else                         band_code = 0x43;

        m88tc6800_write_reg(priv, 0x2f, band_code);
    } else {
        m88tc6800_write_reg(priv, 0x2f, 0x00);
    }

    /* Reg 0x0b bits [1:0]: write normalised band select */
    m88tc6800_set_reg_bits(priv, 0x0b, band_sel, 0x0, 0x1);

    /* Reg 0x32: set to 0x04 for freq in [330000..400000] kHz, else 0x00.
     * Unsigned subtraction wraps for freq < 330000, so values below the
     * base also produce a large result and correctly fall into the 0x00 case. */
    m88tc6800_write_reg(priv, 0x32,
                (freq_KHz - 330000U) < 70001U ? 0x04U : 0x00U);
}

/* Refactored from Ghidra decompilation of _mt_fe_tn_set_LO_tc6800_cxd2856.
 *
 * Variable name mapping from decompilation:
 *   extraout_r0  -> freq_KHz    (function argument, Ghidra artefact)
 *   extraout_r1  -> mixer_sel   (function argument, Ghidra artefact)
 *   bVar2        -> use_path_a  (true when mixer_sel==2 and freq<500000)
 *   reg_data     -> reg14_val   (value written to reg 0x14)
 *   uVar1        -> threshold   (base for the high-freq >=500000 band check)
 *   data         -> vco_data    (value written to reg 0x13 bit field)
 *
 * bVar2 simplification:
 *   Line 14 initialises bVar2 = (freq == 499999), but line 15-17 always
 *   overrides it with (mixer_sel == 2) when freq < 500000.  Since 499999
 *   is always < 500000 the initialiser is always overridden, so:
 *       bVar2  ≡  (mixer_sel == 2) && (freq < 500000)
 *
 * Three paths select (reg14_val, ldiv) based on mixer_sel and frequency:
 *
 *   PATH A — mixer_sel == 2, freq < 500000
 *     freq [      0 ..  62999 ]   reg14=0x8b  ldiv=128
 *     freq [  63000 ..  82999 ]   reg14=0x7a  ldiv= 96
 *     freq [  83000 .. 124999 ]   reg14=0x0a  ldiv= 64
 *     freq [ 125000 .. 166999 ]   reg14=0x0d  ldiv= 48
 *     freq [ 167000 .. 249999 ]   reg14=0x09  ldiv= 32
 *     freq [ 250000 .. 334999 ]   reg14=0x0c  ldiv= 24
 *     freq [ 335000 .. 499999 ]   reg14=0x08  ldiv= 16
 *
 *   PATH B — mixer_sel != 2, NOT (mixer_sel == 3 AND freq >= 250000)
 *     freq [      0 ..  55999 ]   reg14=0x0b  ldiv=128
 *     freq [  56000 ..  82999 ]   reg14=0x7a  ldiv= 96
 *     freq [  83000 .. 124999 ]   reg14=0x0a  ldiv= 64
 *     freq [ 125000 .. 166999 ]   reg14=0x79  ldiv= 48
 *     freq [ 167000 .. 249999 ]   reg14=0x09  ldiv= 32
 *     freq [ 250000 .. 334999 ]   reg14=0x78  ldiv= 24
 *     freq [ 335000 .. 499999 ]   reg14=0x08  ldiv= 16
 *     freq [ 500000 .. 666999 ]   reg14=0x74  ldiv= 12
 *     freq [ 667000 ..   +inf ]   reg14=0x04  ldiv=  8
 *
 *   PATH C — mixer_sel == 3, freq >= 250000  (mixer_sel != 2 implied)
 *     freq [ 250000 .. 332999 ]   reg14=0xf8  ldiv= 24
 *     freq [ 333000 .. 499999 ]   reg14=0x88  ldiv= 16
 *     freq [ 500000 .. 665999 ]   reg14=0x74  ldiv= 12
 *     freq [ 666000 ..   +inf ]   reg14=0x04  ldiv=  8
 *
 * The high-freq thresholds for paths B and C differ by one (666999 vs 665999)
 * because the original uses (uVar1 | 0xa0000) < freq with different uVar1
 * values: 0x2d77 (11575) for B and 0x298f (10639) for C.
 *   B: (0x2d77 | 0xa0000) = 0xa2d77 = 666999  →  freq > 666999 (i.e. >= 667000)
 *   C: (0x298f | 0xa0000) = 0xa298f = 665999  →  freq > 665999 (i.e. >= 666000)
 */
void m88tc6800_set_lo(struct m88tc6800_priv *priv, uint32_t freq_KHz, uint8_t mixer_sel)
{
    uint8_t reg14_val;

    /* ------------------------------------------------------------------
     * Select reg 0x14 value and loop divider (ldiv) based on mixer_sel
     * and frequency band.
     * ------------------------------------------------------------------ */
    if (mixer_sel == 2U && freq_KHz < 500000U) {
        /* PATH A: low-IF mixer, VCO below 500 MHz */
        if      (freq_KHz <  63000U) { reg14_val = 0x8b; priv->int_ldiv = 128; }
        else if (freq_KHz <  83000U) { reg14_val = 0x7a; priv->int_ldiv =  96; }
        else if (freq_KHz < 125000U) { reg14_val = 0x0a; priv->int_ldiv =  64; }
        else if (freq_KHz < 167000U) { reg14_val = 0x0d; priv->int_ldiv =  48; }
        else if (freq_KHz < 250000U) { reg14_val = 0x09; priv->int_ldiv =  32; }
        else if (freq_KHz < 335000U) { reg14_val = 0x0c; priv->int_ldiv =  24; }
        else                         { reg14_val = 0x08; priv->int_ldiv =  16; }

    } else if (mixer_sel == 3U && freq_KHz >= 250000U) {
        /* PATH C: high-side mixer, UHF and above */
        if      (freq_KHz < 333000U) { reg14_val = 0xf8; priv->int_ldiv = 24; }
        else if (freq_KHz < 500000U) { reg14_val = 0x88; priv->int_ldiv = 16; }
        else if (freq_KHz < 666000U) { reg14_val = 0x74; priv->int_ldiv = 12; }
        else                         { reg14_val = 0x04; priv->int_ldiv =  8; }

    } else {
        /* PATH B: all other mixer_sel values (and mixer_sel==3 below 250 MHz) */
        if      (freq_KHz <  56000U) { reg14_val = 0x0b; priv->int_ldiv = 128; }
        else if (freq_KHz <  83000U) { reg14_val = 0x7a; priv->int_ldiv =  96; }
        else if (freq_KHz < 125000U) { reg14_val = 0x0a; priv->int_ldiv =  64; }
        else if (freq_KHz < 167000U) { reg14_val = 0x79; priv->int_ldiv =  48; }
        else if (freq_KHz < 250000U) { reg14_val = 0x09; priv->int_ldiv =  32; }
        else if (freq_KHz < 335000U) { reg14_val = 0x78; priv->int_ldiv =  24; }
        else if (freq_KHz < 500000U) { reg14_val = 0x08; priv->int_ldiv =  16; }
        else if (freq_KHz < 667000U) { reg14_val = 0x74; priv->int_ldiv =  12; }
        else                         { reg14_val = 0x04; priv->int_ldiv =   8; }
    }

    /* ------------------------------------------------------------------
     * Compute target VCO frequency and select VCO band for reg 0x13.
     * fvco_tg = ldiv * freq_KHz
     * Bit field [5:3] of reg 0x13: 0x4 below 6700 MHz, 0x7 above.
     * ------------------------------------------------------------------ */
    priv->fvco_tg = priv->int_ldiv * freq_KHz;

    uint8_t vco_data = (priv->fvco_tg < 6700000U) ? 0x4U : 0x7U;
    m88tc6800_set_reg_bits(priv, 0x13, vco_data, 0x3, 0x5);
    m88tc6800_write_reg(priv, 0x14, reg14_val);
}

/* Refactored from Ghidra decompilation of _mt_fe_tn_set_PLL_freq_tc6800_cxd2856.
 *
 * Variable name mapping from decompilation:
 *   uVar4  -> fvco_tg        (priv->fvco_tg)
 *   uVar3  -> crystal        (priv->config.xtal)
 *   uVar1  -> crystal_half   (crystal / 2)
 *   uVar12 -> crystal_x2     (crystal * 2)
 *   uVar13 -> pll_ref        (selected PLL reference frequency, kHz)
 *   uVar5  -> fdiv_n         (integer+fractional divider word: bits[11:4]=upper, [3:0]=lower)
 *   uVar6  -> fdiv_f / fvco  (fractional part during divider calc, reused for Fvco_KHz later)
 *   uVar14 -> fdiv_n_lo      (FDIV_N[3:0])
 *   uVar15 -> fdiv_n_hi      (FDIV_N[11:4])
 *   cVar9  -> spur_opti      (spur_opti_by_dsm: 0=none, 1=>>1, 2=>>2)
 *   bVar16 -> sdm_en         (pll_sdm_en: fractional mode enabled)
 *   reg_data / local_38      (registers 0x1b / 0x1a: fractional low/high bytes)
 *   uVar6  -> fvco_khz       (Fvco in kHz, after divider reconstruction)
 *   uVar7  -> icp_raw        (ICP intermediate: fvco_khz + 0x100)
 *   uVar17 -> icp_hi         (ICP high-resolution scaled value)
 *   uVar5  -> icp_code       (ICP register byte, reused from fdiv_n)
 *   bVar11 -> icp_code_clamped
 *   bVar2  -> fdiv_n_lo_shifted (uVar14 << 3, for reg 0x19)
 *   iVar10 -> nearest_mult   (nearest 27000-multiple of fvco_tg, for 27 MHz crystal)
 */
void m88tc6800_set_pll(struct m88tc6800_priv *priv)
{
    uint32_t crystal    = priv->config.xtal;
    uint32_t fvco_tg    = priv->fvco_tg;
    uint32_t crystal_half = crystal >> 1;       /* crystal / 2  */
    uint32_t crystal_x2   = crystal * 2;        /* crystal * 2  */

    /* PLL reference divider selection and FDIV_N / FDIV_F computation.
     * pll_ref  : selected reference clock fed to the PLL (kHz)
     * fdiv_n   : combined integer+fractional divider word
     * fdiv_f   : 12-bit fractional part  (bits [11:0] of fdiv_n word)
     * spur_opti: downstream ICP right-shift selector (0/1/2)
     */
    uint32_t pll_ref;
    uint32_t fdiv_n;
    uint32_t fdiv_f;
    uint8_t  spur_opti = 0;

    if (crystal == 24000) {
        /* ----------------------------------------------------------------
         * 24 MHz crystal.
         * Check whether fvco_tg / ldiv falls in the upper Fvco band
         * (above 0x518b1 + 0x176e = 339999 kHz ≈ 340 MHz boundary).
         * If so, use 48 MHz reference; otherwise 24 MHz.
         * Reference step for 24/48 MHz:  ref >> 4  (i.e. ref / 16)
         * but for the straight 24 MHz path the step is 0x5dc (1500).
         * ---------------------------------------------------------------- */
        uint32_t ldiv_quotient = fvco_tg / priv->int_ldiv;

        if (ldiv_quotient - 0x518b1U > 0x176e) {
            pll_ref = 48000;
            fdiv_n  = fvco_tg / (pll_ref >> 4);
            fdiv_f  = (fvco_tg % (pll_ref >> 4)) << 12;
            fdiv_f /= (pll_ref >> 4);
        } else {
            uint32_t ref_step = 0x5dc; /* 1500 kHz */

            pll_ref = 24000;
            fdiv_n  = fvco_tg / ref_step;
            fdiv_f  = (fvco_tg % ref_step) << 12;
            fdiv_f /= ref_step;
        }

    } else if (crystal == 27000) {
        /* ----------------------------------------------------------------
         * 27 MHz crystal.
         * Compute nearest multiple of 27000 to fvco_tg using the
         * compiler-emitted multiply-high approximation for division by
         * 27000:   round(x / 27000) = x/27000 - sign_correction
         * The result (iVar10) is the nearest 27000-multiple.
         *
         * Depending on how far fvco_tg sits from that multiple:
         *   ±10 .. ±1010 kHz  → pll_ref = 18000, spur_opti = 2
         *   +1012 .. +2020 kHz → pll_ref = 18000, spur_opti = 1
         *   within -2020..-1012 kHz → pll_ref = 18000, spur_opti = 1 (via cVar9=true=1)
         *   within ±10 kHz of multiple (no spur) → pll_ref = 54000
         *   otherwise → pll_ref = 18000 or 54000
         * ---------------------------------------------------------------- */

        /* Compiler multiply-high trick: round(fvco_tg / 27000) * 27000 */
        uint32_t q27 = fvco_tg / 27000;
        int32_t  sign_corr = (int32_t)(
            ((uint64_t)(fvco_tg >> 2) * 0x4dac1b9dULL >> 32) << 21
        ) >> 31;
        int32_t  nearest_mult = (int32_t)(q27 - (uint32_t)sign_corr) * 27000;

        if (((uint32_t)nearest_mult + 10U < fvco_tg &&
             fvco_tg < (uint32_t)nearest_mult + 0x3f2U) ||
            (fvco_tg < (uint32_t)nearest_mult - 10U &&
             (uint32_t)nearest_mult - 0x3f2U < fvco_tg)) {
            spur_opti = 2;
            pll_ref   = 18000;
        } else if ((uint32_t)nearest_mult + 0x3fcU < fvco_tg &&
               fvco_tg < (uint32_t)nearest_mult + 0x7e4U) {
            spur_opti = 1;
            pll_ref   = 18000;
        } else if (fvco_tg < (uint32_t)nearest_mult - 0x3fcU) {
            /* spur_opti = (iVar10 - 0x7e4 < fvco_tg) — i.e. 0 or 1 */
            spur_opti = ((uint32_t)nearest_mult - 0x7e4U < fvco_tg) ? 1 : 0;
            pll_ref   = (spur_opti) ? 18000 : 54000;
        } else {
            spur_opti = 0;
            pll_ref   = 54000;
        }

        uint32_t ref_step = pll_ref >> 4;

        fdiv_n = fvco_tg / ref_step;
        fdiv_f = (fvco_tg % ref_step) << 12;
        fdiv_f /= ref_step;

    } else if (crystal_x2 == 9000 || crystal_x2 == 27000) {
        /* ----------------------------------------------------------------
         * crystal = 4500 Hz or 13500 kHz  (crystal*2 == 9000 or 27000).
         * ref_step = crystal_x2 / 8
         * fdiv_n derived from fvco_tg * 2
         * ---------------------------------------------------------------- */
        uint32_t ref_step = crystal_x2 >> 3;
        uint32_t fvco_x2  = fvco_tg << 1;

        pll_ref   = crystal_x2;
        fdiv_n    = fvco_x2 / ref_step;
        fdiv_f    = (fvco_x2 % ref_step) << 12;
        fdiv_f   /= ref_step;
        spur_opti = 0;

    } else if (crystal_x2 == 0x34bc) {
        /* ----------------------------------------------------------------
         * crystal*2 == 13500 (0x34bc = 13500) — special fixed divider.
         * ref divisor = 0xd2f (3375)
         * ---------------------------------------------------------------- */
        pll_ref   = crystal_x2;
        fdiv_n    = (fvco_tg * 4) / 0xd2fU;
        fdiv_f    = ((fvco_tg * 4) % 0xd2fU) * 0x1000U / 0xd2fU;
        spur_opti = 0;

    } else {
        /* ----------------------------------------------------------------
         * Fallback: use the same ref_step as the 27 MHz / 48 MHz path.
         * pll_ref stays crystal_x2; ref_step = pll_ref >> 4.
         * ---------------------------------------------------------------- */
        pll_ref   = crystal_x2;
        uint32_t ref_step = pll_ref >> 4;

        fdiv_n    = fvco_tg / ref_step;
        fdiv_f    = (fvco_tg % ref_step) << 12;
        fdiv_f   /= ref_step;
        spur_opti = 0;
    }

    /* ------------------------------------------------------------------
     * Split fdiv_n into upper (bits [11:4]) and lower nibble (bits [3:0]).
     * fdiv_n_hi : 8-bit field written to regs 0x17/0x18
     * fdiv_n_lo : 4-bit field written (shifted left 3) to reg 0x19
     * ------------------------------------------------------------------ */
    uint32_t fdiv_n_hi = (fdiv_n << 0x12) >> 0x16;  /* bits [11:4] → 8 bits */
    uint32_t fdiv_n_lo = fdiv_n & 0xf;               /* bits [3:0]           */

    /* ------------------------------------------------------------------
     * SDM (fractional) enable decision.
     * The fractional part fdiv_f is valid when its 12-bit value lies in
     * [0x21 .. 0x21 + 0xfbf - 1]  i.e.  [33 .. 4128].
     * Outside that range the PLL runs in integer mode; if the fractional
     * part rounds up (bit 11 set), increment the integer divider by 1.
     * ------------------------------------------------------------------ */
    bool     sdm_en;
    uint8_t  fdiv_frac_hi;  /* reg 0x1a */
    uint8_t  fdiv_frac_lo;  /* reg 0x1b */
    uint32_t frac_contribution;

    if ((fdiv_f & 0xfffU) - 0x21U < 0xfbfU) {
        fdiv_frac_lo     = (uint8_t)fdiv_f;
        sdm_en           = true;
        fdiv_frac_hi     = (uint8_t)((fdiv_f << 0x14) >> 0x1c) | 0x30;
        frac_contribution = (pll_ref * (fdiv_f & 0xfffU)) >> 16;
    } else {
        if (fdiv_f & 0x800U) {
            /* Round up the integer divider */
            fdiv_n_hi = (fdiv_n + 1) * 0x40000U >> 0x16;
            fdiv_n_lo = (fdiv_n + 1) & 0xfU;
        }
        sdm_en            = false;
        fdiv_frac_lo      = 0x00;
        fdiv_frac_hi      = 0x30;
        frac_contribution = 0;
    }

    /* ------------------------------------------------------------------
     * Reconstruct Fvco_KHz from the (now possibly rounded) divider and
     * convert to an ICP current code.
     *
     * Fvco_KHz = pll_ref * fdiv_n_hi + frac_contribution
     *            + (pll_ref * fdiv_n_lo) / 16
     *
     * ICP formula (linear in Fvco):
     *   if Fvco < 8000 MHz:  icp = (32000000 - Fvco_KHz * 4)  / 0x9eb1
     *   else:                icp = -((Fvco_KHz + 0x3f85ee00) * 4) / 0x9eb1
     * ------------------------------------------------------------------ */
    uint32_t fvco_khz = pll_ref * fdiv_n_hi + frac_contribution
                + (pll_ref * fdiv_n_lo >> 4);

    uint32_t icp;
    if (fvco_khz < 8000000U) {
        icp = (fvco_khz * -4 + 32000000U) / 0x9eb1U;
    } else {
        icp = -(((fvco_khz + 0x3f85ee00U) * 4U) / 0x9eb1U);
    }

    uint32_t icp_raw  = icp + 0x100U;
    uint32_t icp_hi   = icp_raw * 0x80000U >> 24;  /* high-res ICP scaled value */
    uint32_t icp_code = ((icp_hi & 1U) + (icp_raw >> 6)) & 0xffU;

    /* ------------------------------------------------------------------
     * Reference divider path selection — programs registers 0x10/0x11/0x15
     * and adjusts icp_code / icp_hi based on which sub-divider is in use.
     * ------------------------------------------------------------------ */
    if (crystal == pll_ref) {
        /* Direct crystal reference (÷1) */
        icp_hi = icp_hi - (uint32_t)((int32_t)(icp << 0x1b) >> 31);

        m88tc6800_write_reg(priv, 0x4e, 0x11);
        m88tc6800_write_reg(priv, 0x4f, 0x11);
        m88tc6800_write_reg(priv, 0x4e, 0x10);
        m88tc6800_write_reg(priv, 0x4f, 0x08);
        m88tc6800_write_reg(priv, 0x4e, 0x15);
        m88tc6800_write_reg(priv, 0x4f, 0x13);

        icp_code = icp_hi & 0xffU;

    } else if (pll_ref == crystal_x2 / 3) {
        /* ÷2/3 reference path */
        icp_hi   = icp_hi - (uint32_t)((int32_t)(icp << 0x1b) >> 31);
        icp_code = (icp_code + icp_hi) & 0xffU;

        m88tc6800_write_reg(priv, 0x4e, 0x11);
        m88tc6800_write_reg(priv, 0x4f, 0x33);
        m88tc6800_write_reg(priv, 0x4e, 0x10);
        m88tc6800_write_reg(priv, 0x4f, 0x0b);
        m88tc6800_write_reg(priv, 0x4e, 0x15);
        m88tc6800_write_reg(priv, 0x4f, 0x43);

    } else if (pll_ref == crystal / 3) {
        /* ÷3 reference path */
        uint32_t icp_x3   = icp_raw * 0x100000U >> 24;
        uint32_t icp_x3_r = icp_x3 & 1U;

        icp_code = ((icp_hi + icp_x3)
                - (uint32_t)((int32_t)(icp << 0x1c) >> 31)
                + icp_x3_r) & 0xffU;

        m88tc6800_write_reg(priv, 0x4e, 0x11);
        m88tc6800_write_reg(priv, 0x4f, 0x33);
        m88tc6800_write_reg(priv, 0x4e, 0x10);
        m88tc6800_write_reg(priv, 0x4f, 0x08);
        m88tc6800_write_reg(priv, 0x4e, 0x15);
        m88tc6800_write_reg(priv, 0x4f, 0x63);

    } else if (crystal_half == pll_ref) {
        /* ÷2 reference path */
        icp_hi   = (icp_raw >> 4)
               - (uint32_t)((int32_t)(icp << 0x1c) >> 31);
        icp_code = icp_hi & 0xffU;

        m88tc6800_write_reg(priv, 0x4e, 0x11);
        m88tc6800_write_reg(priv, 0x4f, 0x22);
        m88tc6800_write_reg(priv, 0x4e, 0x10);
        m88tc6800_write_reg(priv, 0x4f, 0x08);
        m88tc6800_write_reg(priv, 0x4e, 0x15);
        m88tc6800_write_reg(priv, 0x4f, 0x13);

    } else {
        /* Default / other reference ratio */
        m88tc6800_write_reg(priv, 0x4e, 0x11);
        m88tc6800_write_reg(priv, 0x4f, 0x11);
        m88tc6800_write_reg(priv, 0x4e, 0x10);
        m88tc6800_write_reg(priv, 0x4f, 0x0b);
        m88tc6800_write_reg(priv, 0x4e, 0x15);
        m88tc6800_write_reg(priv, 0x4f, 0x13);
    }

    /* ------------------------------------------------------------------
     * SDM enable register (0x12) and ICP scale factor.
     * When SDM is active, decrement icp_code by 1 and signal the hardware.
     * ------------------------------------------------------------------ */
    m88tc6800_write_reg(priv, 0x4e, 0x12);
    if (sdm_en) {
        icp_code = (icp_code - 1U) & 0xffU;
        m88tc6800_write_reg(priv, 0x4f, 0x21);
    } else {
        m88tc6800_write_reg(priv, 0x4f, 0x00);
    }

    /* Apply spur optimisation shift to ICP code */
    if (spur_opti == 1)
        icp_code >>= 1;
    else if (spur_opti == 2)
        icp_code >>= 2;

    /* Clamp ICP code to [2 .. 15] */
    if (icp_code < 2U)
        icp_code = 2U;
    uint8_t icp_code_clamped = (icp_code > 0xeU) ? 0xfU : (uint8_t)icp_code;

    /* ------------------------------------------------------------------
     * Write remaining PLL registers.
     * ------------------------------------------------------------------ */

    /* Fixed configuration registers */
    m88tc6800_write_reg(priv, 0x4e, 0x0a);
    m88tc6800_write_reg(priv, 0x4f, 0x63);
    m88tc6800_write_reg(priv, 0x4e, 0x0f);
    m88tc6800_write_reg(priv, 0x4f, 0x3d);
    m88tc6800_write_reg(priv, 0x4e, 0x0b);
    m88tc6800_write_reg(priv, 0x4f, 0xa1);
    m88tc6800_write_reg(priv, 0x3d, 0xff);
    m88tc6800_write_reg(priv, 0x4e, 0x1c);
    m88tc6800_write_reg(priv, 0x4f, 0x7e);

    /* Reg 0x19: FDIV_N lower nibble (shifted left 3) + VCO calibration trigger bits.
     * SDM mode: write 0x03 first (arm), then 0x07 (trigger).
     * Integer mode: write 0x02 first (arm), then 0x06 (trigger).            */
    uint8_t fdiv_n_lo_shifted = (uint8_t)(fdiv_n_lo << 3);

    m88tc6800_write_reg(priv, 0x4e, 0x19);
    m88tc6800_write_reg(priv, 0x4f, fdiv_n_lo_shifted | (sdm_en ? 0x03 : 0x02));
    m88tc6800_write_reg(priv, 0x4e, 0x19);
    m88tc6800_write_reg(priv, 0x4f, fdiv_n_lo_shifted | (sdm_en ? 0x07 : 0x06));

    /* Regs 0x17/0x18: FDIV_N upper byte (high bits ORed with 0x0c, low byte) */
    m88tc6800_write_reg(priv, 0x4e, 0x17);
    m88tc6800_write_reg(priv, 0x4f, (uint8_t)(fdiv_n_hi >> 8) | 0x0c);
    m88tc6800_write_reg(priv, 0x4e, 0x18);
    m88tc6800_write_reg(priv, 0x4f, (uint8_t)fdiv_n_hi);

    /* Regs 0x1a/0x1b: fractional divider high/low */
    m88tc6800_write_reg(priv, 0x4e, 0x1a);
    m88tc6800_write_reg(priv, 0x4f, fdiv_frac_hi);
    m88tc6800_write_reg(priv, 0x4e, 0x1b);
    m88tc6800_write_reg(priv, 0x4f, fdiv_frac_lo);

    /* Reg 0x0e/0x14: fixed charge pump / LPF settings */
    m88tc6800_write_reg(priv, 0x4e, 0x0e);
    m88tc6800_write_reg(priv, 0x4f, 0x58);
    m88tc6800_write_reg(priv, 0x4e, 0x14);
    m88tc6800_write_reg(priv, 0x4f, 0x4c);

    /* Reg 0x13: ICP code with mode flag in bit 4 */
    m88tc6800_write_reg(priv, 0x4e, 0x13);
    m88tc6800_write_reg(priv, 0x4f, icp_code_clamped | 0x10);
}

void m88tc6800_set_bandwidth(struct m88tc6800_priv *priv, u32 bandwidth_hz)
{
    if (bandwidth_hz == 1700) {
        m88tc6800_write_reg(priv, 0x59, 0x09);
        m88tc6800_write_reg(priv, 0x29, 0xae);
        m88tc6800_write_reg(priv, 0x86, 0x3c);
    }
    else if (bandwidth_hz == 6000) {
        m88tc6800_write_reg(priv, 0x59, 0x0a);
        m88tc6800_write_reg(priv, 0x29, 0xaa);
        m88tc6800_write_reg(priv, 0x86, 0x12);
    }
    else if (bandwidth_hz == 7000) {
        m88tc6800_write_reg(priv, 0x59, 0x0b);
        m88tc6800_write_reg(priv, 0x29, 0xa8);
        m88tc6800_write_reg(priv, 0x86, 0x12);
    }
    else if (bandwidth_hz == 8000) {
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

/* Refactored from Ghidra decompilation of _mt_fe_tn_set_DAC_tc6800_cxd2856.
 *
 * Variable name mapping from decompilation:
 *   uVar1         -> dac            (priv->config.dac, DAC/ADC clock in kHz)
 *   extraout_r0   -> freq_KHz       (function argument, never modified)
 *   cVar4         -> flt_base       (0x40 or 0x80 depending on DAC rate)
 *   uVar7         -> fadc_khz       (selected ADC sample rate, kHz)
 *   uVar6         -> fadc_hz        (selected ADC sample rate, Hz = fadc_khz * 1000)
 *   iVar3         -> fc             (filter centre coefficient)
 *   iVar2         -> ncoi / bw_val  (reused: NCO word, then bandwidth intermediate)
 *   uVar2         -> z1             (filter coefficient z1 = z0 / fc)
 *   extraout_r1   -> ncoi_rem       (remainder of dac*0x7d000 / fadc_hz)
 *   extraout_r1_00 -> z0_frac       (remainder of z0 / fc, fractional bits of z1)
 */
/* Tuner application type codes */
#define TUNER_APP_DVB_T   0x1
#define TUNER_APP_ISDB_T  0x3
#define TUNER_APP_DVB_C   0x4

void m88tc6800_set_dac(struct m88tc6800_priv *priv, uint32_t freq_KHz, uint32_t bandwidth_hz)
{
    uint32_t dac     = priv->config.dac;
    uint32_t crystal = priv->config.xtal;
    uint32_t application = 0;

    /* ------------------------------------------------------------------
     * Reg 0x22: DAC filter bandwidth / gain control.
     * flt_base selects the upper or lower half of the register range
     * based on the DAC clock rate (threshold 0x1195 = 4501 kHz).
     * tuner_dac_gain is scaled by 8 (the '\b' literal = 8) and added.
     * ------------------------------------------------------------------ */
    uint8_t flt_base = (dac < 0x1195U) ? 0x40U : 0x80U;
    m88tc6800_write_reg(priv, 0x22,
                flt_base + (uint8_t)(priv->config.dac_gain * 8U) + 0x05U);

    m88tc6800_set_reg_bits(priv, 0x20, 0x3, 0x5, 0x6);

    /* ------------------------------------------------------------------
     * ADC sample-rate selection (fadc_khz / fadc_hz) and reg 0x06 flt_bit.
     *
     * The outer if/else sets a crystal-dependent default for reg 0x06,
     * then both 24 MHz and 27 MHz paths share the same inner dispatch
     * (the original goto LAB_0008a204 merges them).
     *
     * Special case: freq_KHz == 0xf37ff (997375 kHz) skips the inner
     * dispatch entirely and falls through to the default fadc values.
     *
     * The inner dispatch picks fadc_khz / fadc_hz and writes reg 0x06
     * according to which spectral spur band freq_KHz falls in.
     * Each band test is an unsigned "distance from nearest harmonic < N"
     * check done via: (freq % period) - offset < window  (unsigned arith,
     * so values below 'offset' wrap and are large → fail the test).
     * ------------------------------------------------------------------ */

    /* Default ADC rate (108 MHz); overridden below when needed */
    uint32_t fadc_khz = 0x1a5e0U;     /* 108000 kHz */
    uint32_t fadc_hz  = 108000000U;    /* 108000000 Hz */

    if (crystal == 24000U) {
        m88tc6800_write_reg(priv, 0x4e, 0x06);
        m88tc6800_write_reg(priv, 0x4f, 0x0d);
    } else if (crystal == 27000U) {
        m88tc6800_write_reg(priv, 0x4e, 0x06);
        m88tc6800_write_reg(priv, 0x4f, 0x08);
    }

    /* Inner dispatch — shared by both crystal paths */
    if (freq_KHz != 0xf37ffU) {
        if (crystal == 24000U) {
            /* 24 MHz crystal spur avoidance bands.
             * First gate: check distance from nearest 27 MHz harmonic
             * using the approximation  freq % 27000 ≈
             *   freq - (freq >> 3) / 0xd2f * 27000            */
            uint32_t dist24 = freq_KHz
                      + (freq_KHz >> 3) / 0xd2fU * (uint32_t)-27000
                      - 0xfa1U;
            if (dist24 > 0x4a36U) {
                m88tc6800_write_reg(priv, 0x4e, 0x06);
                m88tc6800_write_reg(priv, 0x4f, 0x12);

                if (freq_KHz % 30000U - 0xfa1U < 21999U) {
                    /* 30 MHz band */
                    fadc_khz = 120000U;
                    fadc_hz  = 120000000U;
                } else {
                    m88tc6800_write_reg(priv, 0x4e, 0x06);
                    m88tc6800_write_reg(priv, 0x4f, 0x16);

                    if (freq_KHz % 0x7e90U - 0xfa1U < 0x5f4fU) {
                        /* 130 kHz band (0x7e90 = 32400) */
                        fadc_khz = 0x1fa40U;   /* 129600 kHz */
                        fadc_hz  = 0x7b98a00U; /* 129,960,960 Hz */
                    } else {
                        m88tc6800_write_reg(priv, 0x4e, 0x06);
                        m88tc6800_write_reg(priv, 0x4f, 0x0f);

                        /* approx freq % 0x6e28 (28200) */
                        uint32_t dist24b = freq_KHz
                                   + (freq_KHz >> 3) / 0xdc5U * (uint32_t)-0x6e28U
                                   - 0xfa1U;
                        if (dist24b < 0x4ee7U) {
                            /* 113 kHz band */
                            fadc_khz = 0x1b8a0U;   /* 112800 kHz */
                            fadc_hz  = 0x6b93100U; /* 112,980,736 Hz */
                        } else {
                            m88tc6800_write_reg(priv, 0x4e, 0x06);
                            m88tc6800_write_reg(priv, 0x4f, 0x11);
                            fadc_khz = 0x1cb60U;   /* 118624 kHz */
                            fadc_hz  = 0x7026f00U; /* 117,350,144 Hz */
                        }
                    }
                }
            }
            /* else: no spur conflict — keep default fadc 108 MHz */

        } else if (crystal == 27000U) {
            /* 27 MHz crystal spur avoidance bands */
            if (freq_KHz % 27000U - 0xfa1U < 18999U) {
                /* 27 MHz harmonic — default 108 MHz ADC rate is fine */
                fadc_khz = 0x1a5e0U;
                fadc_hz  = 108000000U;
            } else {
                m88tc6800_write_reg(priv, 0x4e, 0x06);
                m88tc6800_write_reg(priv, 0x4f, 0x0c);

                if (freq_KHz % 0x7404U - 0xfa1U < 0x54c3U) {
                    /* 0x7404 = 29700 kHz band */
                    fadc_khz = 0x1d010U;   /* 118800 kHz */
                    fadc_hz  = 0x714be80U; /* 118,964,352 Hz */
                } else {
                    m88tc6800_write_reg(priv, 0x4e, 0x06);
                    m88tc6800_write_reg(priv, 0x4f, 0x10);

                    if (freq_KHz % 0x7e90U - 0xfa1U < 0x5f4fU) {
                        /* 0x7e90 = 32400 kHz band */
                        fadc_khz = 0x1fa40U;   /* 129600 kHz */
                        fadc_hz  = 0x7b98a00U; /* 129,960,960 Hz */
                    } else {
                        m88tc6800_write_reg(priv, 0x4e, 0x06);
                        m88tc6800_write_reg(priv, 0x4f, 0x0a);

                        if (freq_KHz % 0x6ebeU - 0xfa1U < 0x4f7dU) {
                            /* 0x6ebe = 28350 kHz band */
                            fadc_khz = 0x1baf8U;   /* 113400 kHz */
                            fadc_hz  = 0x6c258c0U; /* 113,540,288 Hz */
                        } else {
                            m88tc6800_write_reg(priv, 0x4e, 0x06);
                            m88tc6800_write_reg(priv, 0x4f, 0x0b);
                            fadc_khz = 0x1c584U;   /* 116100 kHz */
                            fadc_hz  = 0x6eb8ba0U; /* 116,523,936 Hz */
                        }
                    }
                }
            }

            /* Special override for freq 0x79ac9 (498,377 kHz) */
            if (freq_KHz == 0x79ac9U) {
                m88tc6800_write_reg(priv, 0x4e, 0x06);
                m88tc6800_write_reg(priv, 0x4f, 0x04);
            }
        }
    }

    /* ------------------------------------------------------------------
     * NCO (numerically controlled oscillator) register calculation.
     *
     * NCOI = ( (dac * 0x7d000) / fadc_hz * 32
     *        + (dac * 0x7d000) % fadc_hz * 32 / fadc_hz ) * 4
     *
     * Written as a 16-bit value to regs 0xfa (high byte) / 0xfb (low byte).
     * ------------------------------------------------------------------ */
    uint32_t dac_scaled  = dac * 0x7d000U;
    uint32_t ncoi_int    = dac_scaled / fadc_hz;
    uint32_t ncoi_rem    = dac_scaled % fadc_hz;
    uint32_t ncoi        = (ncoi_int * 0x20U + (ncoi_rem << 5) / fadc_hz) * 4U;

    m88tc6800_write_reg(priv, 0xfa, (uint8_t)(ncoi >> 8));
    m88tc6800_write_reg(priv, 0xfb, (uint8_t)ncoi);

    /* ------------------------------------------------------------------
     * Filter coefficient (fc) calculation.
     *
     * bw_scaled is derived from tuner_bandwidth and tuner_application:
     *   application 3 (ISDB-T):  bw_scaled = (bw/2 - 150) * 108000
     *   application 4 (DVB-C):   bw_scaled = 418,000,000  when bw == 8000 kHz
     *                             bw_scaled = (bw/2 - 100) * 108000  otherwise
     *   application 1 (DVB-T):   bw_scaled = (bw/2 - 140) * 108000
     *   default:                  bw_scaled = (bw/2 - 100) * 108000
     *
     * fc = bw_scaled / fadc_khz
     * ------------------------------------------------------------------ */
    uint32_t bw_scaled;

    if (application == TUNER_APP_ISDB_T) {
        bw_scaled = ((bandwidth_hz >> 1) - 0x96U) * 0x1a5e0U;
    } else if (application == TUNER_APP_DVB_C) {
        if (bandwidth_hz == 8000U)
            bw_scaled = 0x18c89ac0U;   /* 418,000,000 — fixed for 8 MHz DVB-C */
        else
            bw_scaled = ((bandwidth_hz >> 1) - 100U) * 0x1a5e0U;
    } else {
        uint32_t bw_offset = (application == TUNER_APP_DVB_T)
                     ? 0x8cU   /* 140 kHz */
                     : 100U;
        bw_scaled = ((bandwidth_hz >> 1) - bw_offset) * 0x1a5e0U;
    }

    uint32_t fc      = bw_scaled / fadc_khz;

    /* ------------------------------------------------------------------
     * Filter register values derived from fc.
     *
     * z0      = (0x1000 - fc) * 0x8000
     * z1      = z0 / fc            (regs 0xe4/0xe5, low 16 bits)
     * z0_frac = z0 % fc            (fractional bits written to 0xe0/0xe1)
     * fc      written to regs 0xe2/0xe3
     * f3val   = fc * 16 - 0x8000   (regs 0xf3/0xf4)
     * ------------------------------------------------------------------ */
    uint32_t z0      = (0x1000U - fc) * 0x8000U;
    uint32_t z1      = z0 / fc;
    uint32_t z0_frac = z0 % fc;

    m88tc6800_write_reg(priv, 0xe0, (uint8_t)((z0_frac << 0x14) >> 0x1c));
    m88tc6800_write_reg(priv, 0xe1, (uint8_t)z0_frac);
    m88tc6800_write_reg(priv, 0xe2, (uint8_t)(fc >> 8));
    m88tc6800_write_reg(priv, 0xe3, (uint8_t)fc);
    m88tc6800_write_reg(priv, 0xe4, (uint8_t)((uint16_t)z1 >> 8));
    m88tc6800_write_reg(priv, 0xe5, (uint8_t)(uint16_t)z1);

    m88tc6800_write_reg(priv, 0xef, 0x00);
    m88tc6800_write_reg(priv, 0xf0, 0x00);
    m88tc6800_write_reg(priv, 0xf1, 0x08);

    /* f3val = (fc << 4) - 0x8000
     * Original: ((uint)(iVar3 << 0xf) >> 0xb) - 0x8000
     *         = (fc * 0x8000 * 2 >> 11) - 0x8000
     *         = (fc << 4) - 0x8000                      */
    uint32_t f3val = ((uint32_t)(fc << 0xf) >> 0xb) - 0x8000U;

    m88tc6800_write_reg(priv, 0xf2, 0x00);
    m88tc6800_write_reg(priv, 0xf3, (uint8_t)(f3val >> 8));
    m88tc6800_write_reg(priv, 0xf4, (uint8_t)f3val);
}

/* Refactored from Ghidra decompilation of mt_fe_tn_set_freq_tc6800_cxd2856.
 *
 * Variable name mapping from decompilation:
 *   freq_KHz_00  -> freq_KHz    (copy of argument, Ghidra artefact)
 *   uVar1        -> ret / freq  (reused: init return value, later tuner_freq)
 *   uVar8        -> mixer_sel   (mixer path selector, uint16_t in original)
 *   uVar3        -> app / reg_val (reused scratch)
 *   uVar5        -> tmp         (general scratch)
 *   uVar9        -> tmp2        (general scratch)
 *   bVar6        -> reg_byte    (single-byte register read scratch)
 *   bVar10/11    -> dead intermediates for mixer_sel computation (see below)
 *   local_37     -> app_buf     (multi-purpose byte: application read-back,
 *                                then current_app, then reg 0x9a scratch)
 *   local_36     -> lt_buf      (reg 0x9a loop-through byte)
 *   local_35     -> lna_buf     (reg 0x8b LNA state byte)
 *   local_31[0]  -> buf         (general single-byte read buffer)
 *   wait_time*   -> passed through to _mt_fe_tn_set_tune_tc6800_cxd2856
 *
 * Goto elimination:
 *
 *   LAB_0008b808 — skipped `mixer_sel = 3` for the harmonic-imp auto-select
 *   case where freq is outside spur regions.  Replaced with a complete
 *   if/else chain that assigns mixer_sel directly.
 *
 *   LAB_0008d1cc — shared `if (application == 3)` check appended to both
 *   the application-in-{3,4} block and the application==1 block.  Both
 *   branches now end with the same inline check.
 *
 *   LAB_0008c440 — skipped the `write(0x60, 0x34)` for application==3.
 *   Replaced with a conditional write.
 *
 *   LAB_0008c7a0 — shared reg-0x9a read / reg-0x1c conditional write
 *   block reached from two sites inside the loop-through post-tune path.
 *   Inlined at both sites.
 *
 *   LAB_0008c35c — shared `write(0x0d, 0xc4)` reached when not in
 *   cable-mode-2.  Inlined in each branch.
 *
 * Dead code:
 *   Lines 730–1019 in the original are guarded by `if (false)` — a
 *   loop-through calibration block that Ghidra reconstructed but the
 *   original developer disabled.  The two additional gotos inside that
 *   block (LAB_0008c710, LAB_0008d814) are therefore unreachable and
 *   have been dropped along with the block itself.
 *   The commented-out `_mt_fe_tn_get_reg_tc6800_cxd2856(0x3e, ...)` and
 *   `_mt_fe_tn_get_reg_tc6800_cxd2856(0x3c, ...)` calls are also
 *   preserved as comments.
 *
 * mixer_sel auto-selection (when tuner_mixer_type not in {1,2,3}):
 *   freq < 334001:                          mixer_sel = 2
 *   freq in [334001..624000]:               mixer_sel = 3  (harmonic_imp==1, app==0)
 *   freq in [624001..799999]:               mixer_sel = 1  (spur-free band)
 *   freq in [800000..820000]:               mixer_sel = 3  (in-band spur)
 *   freq > 820000:                          mixer_sel = 1
 *   harmonic_imp==1 && application!=0:      mixer_sel = 3
 *   harmonic_imp==0:                        mixer_sel = 1
 * The unsigned subtraction (freq-610000 > 13999 etc.) logic in the original
 * simplifies to the ranges above after resolving bVar10/bVar11.
 */
//struct m88tc6800_priv {
//    uint32_t tuner_clock_out;
//    uint32_t tuner_gpio_out;
//};

int m88tc6800_set_freq(struct m88tc6800_priv *priv, uint32_t freq_KHz, uint32_t bandwidth_hz)
{
    uint8_t  app_buf  = 0;
    uint8_t  lt_buf   = 0;
    uint8_t  lna_buf  = 0;
    uint8_t  buf;
    uint8_t  reg_byte;
    uint32_t application = 0;
    uint32_t clock_out = 0;
    uint32_t gpio_out = 0;

    /* ------------------------------------------------------------------
     * Application mode register synchronisation.
     * Read back the current hardware application setting (reg 0x3e bits
     * [4:1]) and update if it differs from the configured application.
     * Bits [4:1] encode the previous application as a 4-bit field / 2.
     * ------------------------------------------------------------------ */
    m88tc6800_read_reg(priv, 0x3e, &app_buf);
    app_buf &= 0x1eU;

    if (app_buf == 0x1eU) {
        /* Hardware reports all-ones: full reset needed */
        m88tc6800_set_reg_bits(priv, 0x3c, 0x0, 0x7, 0x7);
        app_buf = (uint8_t)application;
        m88tc6800_set_reg_bits(priv, 0x3e,
                    (uint8_t)application, 0x1, 0x4);
    } else {
        uint32_t current_app = app_buf >> 1;
        app_buf = (uint8_t)current_app;

        if (current_app != application) {
            if (current_app == 3U) {
                /* Transitioning away from ISDB-T */
                if (application == 4U) {
                    if (gpio_out == 0x0U)
                        m88tc6800_set_reg_bits(priv, 0x37,
                                    0x6, 0x0, 0x2);
                } else {
                    /* Any other transition from ISDB-T: full reset */
                    m88tc6800_set_reg_bits(priv, 0x3c, 0x0, 0x7, 0x7);
                }
            } else if (application == 3U && current_app == 4U) {
                /* Transitioning into ISDB-T from DVB-C */
                m88tc6800_set_reg_bits(priv, 0x37, 0x0, 0x1, 0x2);
            } else {
                /* All other application transitions: full reset */
                m88tc6800_set_reg_bits(priv, 0x3c, 0x0, 0x7, 0x7);
            }
            app_buf = (uint8_t)application;
            m88tc6800_set_reg_bits(priv, 0x3e,
                        (uint8_t)application, 0x1, 0x4);
        }
    }

    /* ------------------------------------------------------------------
     * PLL power state and sysmon setup.
     * Read reg 0x07 bit 3 (sysmon_on).  If clear, a full power-on
     * sequence is needed including reg 0x0c; if set, skip reg 0x0c.
     * ------------------------------------------------------------------ */
    buf = 0;
    m88tc6800_read_reg(priv, 0x07, &buf);
    reg_byte = buf & 0x08U;

    if (reg_byte == 0U) {
        /* sysmon was off: enable via 0x0c sequence */
        m88tc6800_write_reg(priv, 0x0c, 0x63);
        m88tc6800_write_reg(priv, 0x07, 0x0d);
        m88tc6800_write_reg(priv, 0x0c, 0xe3);
        m88tc6800_write_reg(priv, 0x11, reg_byte);
    } else {
        /* sysmon already on */
        m88tc6800_write_reg(priv, 0x07, 0x0d);
        m88tc6800_write_reg(priv, 0x11, 0x00);
    }

    /* ------------------------------------------------------------------
     * Power-on initialisation block.
     * Only executed when the tuner is cold (reg 0x3c bit 7 was clear).
     * app_buf retains the masked & shifted reg 0x3e value from above;
     * after masking with 0x80 this detects the power-good bit.
     *
     * NOTE: The original read of reg 0x3c into app_buf at this point is
     * commented out in the source (`//_mt_fe_tn_get_reg_tc6800_cxd2856`).
     * The 0x80 mask is applied to whatever app_buf holds, which is the
     * tuner_application value written above — so this block is never
     * entered when application < 128.  The `if (false)` guard confirms
     * this is intentionally disabled.
     * ------------------------------------------------------------------ */
    reg_byte = app_buf & 0x80U;
    /* if (reg_byte == 0) — disabled in original source */
    if (false) {
        uint8_t data1 = 0, data2 = 0;
        uint8_t local_32 = 0;

        m88tc6800_set_reg_bits(priv, 0x3c, 0x1, 0x0, 0x0);
        m88tc6800_set_reg_bits(priv, 0x55, 0x1, 0x0, 0x0);

        if (clock_out == 0x1U) {
            m88tc6800_write_reg(priv, 0x16, 0x80);
            m88tc6800_write_reg(priv, 0x17, 0xf3);
        } else {
            m88tc6800_write_reg(priv, 0x16, 0x00);
        }

        uint8_t xtal_cap = (uint8_t)priv->config.xtal_cap;
        if (priv->config.xtal_cap != 0x18U) {
            m88tc6800_write_reg(priv, 0x1a, 0x04);
            m88tc6800_write_reg(priv, 0x1b, xtal_cap);
            m88tc6800_write_reg(priv, 0x1a, 0x05);
            m88tc6800_write_reg(priv, 0x1b, xtal_cap);
        }

        m88tc6800_write_reg(priv, 0x0e, 0xa4);
        m88tc6800_write_reg(priv, 0x03, 0x00);
        m88tc6800_write_reg(priv, 0x4e, 0x02);
        m88tc6800_write_reg(priv, 0x4f, 0xe9);
        m88tc6800_write_reg(priv, 0x68, 0x0f);
        m88tc6800_write_reg(priv, 0x69, 0xf1);
        m88tc6800_write_reg(priv, 0x76, 0x30);
        m88tc6800_write_reg(priv, 0x78, 0x25);
        m88tc6800_write_reg(priv, 0x79, 0x1f);
        m88tc6800_write_reg(priv, 0x7b, 0x00);

        if ((application - 3U) < 2U) {
            m88tc6800_write_reg(priv, 0xb1, 0x1a);
            m88tc6800_write_reg(priv, 0xb2, 0x6f);
            m88tc6800_write_reg(priv, 0xb3, 0x34);
            m88tc6800_write_reg(priv, 0xb4, 0x45);
            m88tc6800_write_reg(priv, 0xb5, 0x1a);
            m88tc6800_write_reg(priv, 0xb6, 0x6f);
            m88tc6800_write_reg(priv, 0xba, 0x9a);
        } else {
            m88tc6800_write_reg(priv, 0xb1, 0x2a);
            m88tc6800_write_reg(priv, 0xb2, 0xb2);
            m88tc6800_write_reg(priv, 0xb3, 0x54);
            m88tc6800_write_reg(priv, 0xb4, 0x6e);
            m88tc6800_write_reg(priv, 0xb5, 0x2a);
            m88tc6800_write_reg(priv, 0xb6, 0xb2);
            m88tc6800_write_reg(priv, 0xba, 0x90);
        }

        m88tc6800_write_reg(priv, 0x27, 0xb4);
        m88tc6800_write_reg(priv, 0x25, 0x2a);
        m88tc6800_write_reg(priv, 0x84, 0x20);
        m88tc6800_set_reg_bits(priv, 0xfc, 0x1, 0x5, 0x5);
        m88tc6800_set_reg_bits(priv, 0x2a, 0x1, 0x0, 0x1);
        m88tc6800_set_reg_bits(priv, 0xa7, 0x0, 0x0, 0x2);
        m88tc6800_write_reg(priv, 0x2c, 0x0a);
        m88tc6800_write_reg(priv, 0xc7, 0x02);
        m88tc6800_write_reg(priv, 0x05, 0x04);
        m88tc6800_write_reg(priv, 0xc6, 0x80);
        m88tc6800_write_reg(priv, 0x05, 0x00);
        m88tc6800_write_reg(priv, 0xad, 0x0a);
        m88tc6800_write_reg(priv, 0xfd, 0x1a);

        uint8_t uVar3 = (uint8_t)application;

        if ((application - 3U) < 2U) {
            m88tc6800_write_reg(priv, 0x05, 0x04);
            m88tc6800_write_reg(priv, 0xc7, 0x03);
            m88tc6800_write_reg(priv, 0x05, 0x00);
            m88tc6800_write_reg(priv, 0x30, 0x2f);
            m88tc6800_write_reg(priv, 0x39, 0x05); m88tc6800_write_reg(priv, 0x3a, 0x08);
            m88tc6800_write_reg(priv, 0x39, 0x06); m88tc6800_write_reg(priv, 0x3a, 0x4e);
            m88tc6800_write_reg(priv, 0x39, 0x07); m88tc6800_write_reg(priv, 0x3a, 0x0c);
            m88tc6800_write_reg(priv, 0x39, 0x08); m88tc6800_write_reg(priv, 0x3a, 0x03);
            m88tc6800_write_reg(priv, 0x39, 0x09); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0a); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0b); m88tc6800_write_reg(priv, 0x3a, 0x27);
            m88tc6800_write_reg(priv, 0x39, 0x0c); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0d); m88tc6800_write_reg(priv, 0x3a, 0x08);
            m88tc6800_write_reg(priv, 0x39, 0x11); m88tc6800_write_reg(priv, 0x3a, 0x18);
            m88tc6800_write_reg(priv, 0x39, 0x12); m88tc6800_write_reg(priv, 0x3a, 0x6a);
            m88tc6800_write_reg(priv, 0x39, 0x13); m88tc6800_write_reg(priv, 0x3a, 0x0c);
            m88tc6800_write_reg(priv, 0x39, 0x14); m88tc6800_write_reg(priv, 0x3a, 0x07);
            m88tc6800_write_reg(priv, 0x39, 0x15); m88tc6800_write_reg(priv, 0x3a, 0x01);
            m88tc6800_write_reg(priv, 0x39, 0x16); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x17); m88tc6800_write_reg(priv, 0x3a, 0x35);
            m88tc6800_write_reg(priv, 0x39, 0x18); m88tc6800_write_reg(priv, 0x3a, 0x01);
            m88tc6800_write_reg(priv, 0x39, 0x19); m88tc6800_write_reg(priv, 0x3a, 0x18);
            m88tc6800_write_reg(priv, 0x39, 0x1a); m88tc6800_write_reg(priv, 0x3a, 0x08);
            m88tc6800_write_reg(priv, 0x39, 0x1b); m88tc6800_write_reg(priv, 0x3a, 0x0d);
            m88tc6800_write_reg(priv, 0x39, 0x1c); m88tc6800_write_reg(priv, 0x3a, 0x24);
            m88tc6800_write_reg(priv, 0x39, 0x1d); m88tc6800_write_reg(priv, 0x3a, 0x2a);
            m88tc6800_write_reg(priv, 0x39, 0x0e); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0f); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x10); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x4e, 0x2b); m88tc6800_write_reg(priv, 0x4f, 0x0a);
            m88tc6800_write_reg(priv, 0x4e, 0x2c); m88tc6800_write_reg(priv, 0x4f, 0x29);
            m88tc6800_write_reg(priv, 0x4e, 0x2f); m88tc6800_write_reg(priv, 0x4f, 0x08);
            m88tc6800_write_reg(priv, 0x4e, 0x29); m88tc6800_write_reg(priv, 0x4f, 0xee);
            uVar3 = 0x0d;
        } else if (application == 1U) {
            m88tc6800_write_reg(priv, 0x05, 0x04);
            m88tc6800_write_reg(priv, 0xc7, uVar3);
            m88tc6800_write_reg(priv, 0x05, 0x00);
            m88tc6800_write_reg(priv, 0x30, 0x2f);
            m88tc6800_write_reg(priv, 0x39, 0x05); m88tc6800_write_reg(priv, 0x3a, 0x3f);
            m88tc6800_write_reg(priv, 0x39, 0x06); m88tc6800_write_reg(priv, 0x3a, 0x03);
            m88tc6800_write_reg(priv, 0x39, 0x07); m88tc6800_write_reg(priv, 0x3a, 0x0c);
            m88tc6800_write_reg(priv, 0x39, 0x08); m88tc6800_write_reg(priv, 0x3a, 0x04);
            m88tc6800_write_reg(priv, 0x39, 0x09); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0a); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0b); m88tc6800_write_reg(priv, 0x3a, uVar3);
            m88tc6800_write_reg(priv, 0x39, 0x0c); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0d); m88tc6800_write_reg(priv, 0x3a, 0x7f);
            m88tc6800_write_reg(priv, 0x39, 0x11); m88tc6800_write_reg(priv, 0x3a, 0x3f);
            m88tc6800_write_reg(priv, 0x39, 0x12); m88tc6800_write_reg(priv, 0x3a, 0x0b);
            m88tc6800_write_reg(priv, 0x39, 0x13); m88tc6800_write_reg(priv, 0x3a, 0x09);
            m88tc6800_write_reg(priv, 0x39, 0x14); m88tc6800_write_reg(priv, 0x3a, 0x07);
            m88tc6800_write_reg(priv, 0x39, 0x15); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x16); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x17); m88tc6800_write_reg(priv, 0x3a, 0x05);
            m88tc6800_write_reg(priv, 0x39, 0x18); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x19); m88tc6800_write_reg(priv, 0x3a, 0x7f);
            m88tc6800_write_reg(priv, 0x39, 0x1a); m88tc6800_write_reg(priv, 0x3a, 0x0d);
            m88tc6800_write_reg(priv, 0x39, 0x1b); m88tc6800_write_reg(priv, 0x3a, 0x12);
            m88tc6800_write_reg(priv, 0x39, 0x1c); m88tc6800_write_reg(priv, 0x3a, 0x28);
            m88tc6800_write_reg(priv, 0x39, 0x1d); m88tc6800_write_reg(priv, 0x3a, 0x2e);
            m88tc6800_write_reg(priv, 0x39, 0x0e); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0f); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x10); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x4e, 0x2b); m88tc6800_write_reg(priv, 0x4f, 0x0a);
            m88tc6800_write_reg(priv, 0x4e, 0x2c); m88tc6800_write_reg(priv, 0x4f, 0x20);
            m88tc6800_write_reg(priv, 0x4e, 0x2f); m88tc6800_write_reg(priv, 0x4f, 0x02);
            m88tc6800_write_reg(priv, 0x4e, 0x29); m88tc6800_write_reg(priv, 0x4f, 0xcc);
            uVar3 = 0x0f;
        } else {
            m88tc6800_write_reg(priv, 0x05, 0x04);
            m88tc6800_write_reg(priv, 0xc7, 0x00);
            m88tc6800_write_reg(priv, 0x05, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x05); m88tc6800_write_reg(priv, 0x3a, 0x3f);
            m88tc6800_write_reg(priv, 0x39, 0x06); m88tc6800_write_reg(priv, 0x3a, 0x03);
            m88tc6800_write_reg(priv, 0x39, 0x07); m88tc6800_write_reg(priv, 0x3a, 0x0d);
            m88tc6800_write_reg(priv, 0x39, 0x08); m88tc6800_write_reg(priv, 0x3a, 0x09);
            m88tc6800_write_reg(priv, 0x39, 0x09); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0a); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0b); m88tc6800_write_reg(priv, 0x3a, 0x01);
            m88tc6800_write_reg(priv, 0x39, 0x0c); m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x0d); m88tc6800_write_reg(priv, 0x3a, 0x7f);
            m88tc6800_write_reg(priv, 0x39, 0x1a); m88tc6800_write_reg(priv, 0x3a, 0x08);
            m88tc6800_write_reg(priv, 0x39, 0x1b); m88tc6800_write_reg(priv, 0x3a, 0x0d);
            m88tc6800_write_reg(priv, 0x39, 0x0e); m88tc6800_write_reg(priv, 0x3a, 0x04);
            m88tc6800_write_reg(priv, 0x39, 0x0f); m88tc6800_write_reg(priv, 0x3a, 0x04);
            m88tc6800_write_reg(priv, 0x39, 0x10); m88tc6800_write_reg(priv, 0x3a, 0x01);
            m88tc6800_write_reg(priv, 0x4e, 0x2b); m88tc6800_write_reg(priv, 0x4f, 0x0a);
            m88tc6800_write_reg(priv, 0x4e, 0x2c); m88tc6800_write_reg(priv, 0x4f, 0x10);
            m88tc6800_write_reg(priv, 0x4e, 0x2f); m88tc6800_write_reg(priv, 0x4f, 0x01);
            m88tc6800_write_reg(priv, 0x4e, 0x29); m88tc6800_write_reg(priv, 0x4f, 0xcc);
            uVar3 = 0x10;
        }

        m88tc6800_write_reg(priv, 0x7c, uVar3);
        m88tc6800_set_reg_bits(priv, 0x35, 0x0, 0x4, 0x7);

        if (application == 0x3U)
            m88tc6800_set_reg_bits(priv, 0x37, 0x0, 0x1, 0x2);
        else if (gpio_out == 0x0U)
            m88tc6800_set_reg_bits(priv, 0x37, 0x6, 0x0, 0x2);

        m88tc6800_set_reg_bits(priv, 0xbd, 0x1, 0x7, 0x7);

        if ((application - 3U) < 2U) {
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x40);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x41);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x42);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x4a);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x52);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x5a);
            m88tc6800_write_reg(priv, 0xb8, 0x02); m88tc6800_write_reg(priv, 0xbe, 0x5a);
            m88tc6800_write_reg(priv, 0xb8, 0x02); m88tc6800_write_reg(priv, 0xbe, 0x9a);
            m88tc6800_write_reg(priv, 0xb8, 0x02); m88tc6800_write_reg(priv, 0xbe, 0xda);
            m88tc6800_write_reg(priv, 0xb8, 0x03); m88tc6800_write_reg(priv, 0xbe, 0x1a);
            m88tc6800_write_reg(priv, 0xb8, 0x03); m88tc6800_write_reg(priv, 0xbe, 0x5a);
            m88tc6800_write_reg(priv, 0xb8, 0x05); m88tc6800_write_reg(priv, 0xbe, 0x5a);
            m88tc6800_write_reg(priv, 0xb8, 0x07); m88tc6800_write_reg(priv, 0xbe, 0x5a);
            m88tc6800_write_reg(priv, 0xb8, 0x07);
            uVar3 = 0x9a;
        } else {
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x40);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x41);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x42);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x4a);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x52);
            m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x5a);

            if (application == 1U) {
                m88tc6800_write_reg(priv, 0xb8, 0x02); m88tc6800_write_reg(priv, 0xbe, 0x5a);
                m88tc6800_write_reg(priv, 0xb8, 0x02); m88tc6800_write_reg(priv, 0xbe, 0x9a);
                m88tc6800_write_reg(priv, 0xb8, 0x02); m88tc6800_write_reg(priv, 0xbe, 0xda);
                m88tc6800_write_reg(priv, 0xb8, 0x03); m88tc6800_write_reg(priv, 0xbe, 0x1a);
                m88tc6800_write_reg(priv, 0xb8, 0x03);
                uVar3 = 0x5a;
            } else {
                m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0x62);
                m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0xa2);
                m88tc6800_write_reg(priv, 0xb8, 0x00); m88tc6800_write_reg(priv, 0xbe, 0xe2);
                m88tc6800_write_reg(priv, 0xb8, 0x01); m88tc6800_write_reg(priv, 0xbe, 0x22);
                m88tc6800_write_reg(priv, 0xb8, 0x01);
                uVar3 = 0x62;
            }
            m88tc6800_write_reg(priv, 0xbe, uVar3);
            m88tc6800_write_reg(priv, 0xb8, 0x03); m88tc6800_write_reg(priv, 0xbe, 0x62);
            m88tc6800_write_reg(priv, 0xb8, 0x05); m88tc6800_write_reg(priv, 0xbe, 0x62);
            m88tc6800_write_reg(priv, 0xb8, 0x05);
            uVar3 = 0xa2;
        }

        m88tc6800_write_reg(priv, 0xbe, uVar3);
        m88tc6800_write_reg(priv, 0xb8, 0x07); m88tc6800_write_reg(priv, 0xbe, 0xa2);
        m88tc6800_write_reg(priv, 0xb8, 0x07); m88tc6800_write_reg(priv, 0xbe, 0xaa);
        m88tc6800_write_reg(priv, 0xb8, 0x07); m88tc6800_write_reg(priv, 0xbe, 0xb2);
        m88tc6800_write_reg(priv, 0xb8, 0x07); m88tc6800_write_reg(priv, 0xbe, 0xb3);
        m88tc6800_write_reg(priv, 0xa0, 0x0c);
        m88tc6800_write_reg(priv, 0x39, 0x6a); m88tc6800_write_reg(priv, 0x3a, 0x3f);
        m88tc6800_set_reg_bits(priv, 0x1d, 0x0, 0x1, 0x1);
        m88tc6800_write_reg(priv, 0x4e, 0x05); m88tc6800_write_reg(priv, 0x4f, 0xc0);
        m88tc6800_write_reg(priv, 0x4e, 0x05); m88tc6800_write_reg(priv, 0x4f, 0x80);
        m88tc6800_write_reg(priv, 0x45, 0x5d);

        uint32_t wait_time = 0;
        char cal_retries = 4;
        //m88tc6800_tune(priv, 0xf37ff, 0x32, wait_time);
        m88tc6800_write_reg(priv, 0x14, 0x7b);
        m88tc6800_write_reg(priv, 0x12, 0x1e);
        m88tc6800_set_reg_bits(priv, 0xbd, 0x1, 0x4, 0x4);
        m88tc6800_set_reg_bits(priv, 0xbc, 0x3, 0x6, 0x7);
        //m88tc6800_set_reg_bits_expand(priv, 0x53, 0x0a, 0x0, 0x7, 0x7);
        //m88tc6800_set_reg_bits_expand(priv, 0x53, 0x0d, 0x0, 0x7, 0x7);
        //m88tc6800_set_reg_bits_expand(priv, 0x53, 0x14, 0x1, 0x6, 0x6);
        m88tc6800_write_reg(priv, 0x53, 0x03); m88tc6800_write_reg(priv, 0x54, 0x5a);
        m88tc6800_write_reg(priv, 0x53, 0x04); m88tc6800_write_reg(priv, 0x54, 0xc4);

        do {
            m88tc6800_write_reg(priv, 0x53, 0x01); m88tc6800_write_reg(priv, 0x54, 0x00);
            m88tc6800_write_reg(priv, 0x53, 0x00);
            cal_retries--;
            m88tc6800_write_reg(priv, 0x54, 0xff);
            m88tc6800_write_reg(priv, 0x53, 0x00); m88tc6800_write_reg(priv, 0x54, 0x00);
            //m88tc6800_set_reg_bits_expand(priv, 0x53, 0x02, 0x1, 0x6, 0x6);
            //m88tc6800_set_reg_bits_expand(priv, 0x53, 0x02, 0x0, 0x6, 0x6);
            m88tc6800_write_reg(priv, 0x53, 0x01); m88tc6800_write_reg(priv, 0x54, 0x3a);
            m88tc6800_write_reg(priv, 0x53, 0x06);
            m88tc6800_read_reg(priv, 0x54, &data1);
            m88tc6800_write_reg(priv, 0x53, 0x08);
            m88tc6800_read_reg(priv, 0x54, &data2);
            m88tc6800_read_reg(priv, 0x50, &local_32);
            if (((data1 - 0x2c) < 3) && ((data2 - 0x2c) < 3) &&
                ((uint8_t)(local_32 + 0x3b) < 4))
                break;
        } while (cal_retries != 0);

        m88tc6800_write_reg(priv, 0x53, 0x01); m88tc6800_write_reg(priv, 0x54, 0x00);
        m88tc6800_write_reg(priv, 0x12, 0x0e);
        m88tc6800_set_reg_bits(priv, 0xbd, 0x0, 0x4, 0x4);
        m88tc6800_write_reg(priv, 0x53, 0x0a); m88tc6800_write_reg(priv, 0x54, 0x80);
        m88tc6800_write_reg(priv, 0x53, 0x0b); m88tc6800_write_reg(priv, 0x54, 0x00);
        m88tc6800_write_reg(priv, 0x53, 0x0c); m88tc6800_write_reg(priv, 0x54, 0x00);
        m88tc6800_write_reg(priv, 0x53, 0x0d); m88tc6800_write_reg(priv, 0x54, 0x80);
        m88tc6800_write_reg(priv, 0x53, 0x0e); m88tc6800_write_reg(priv, 0x54, 0x00);
        m88tc6800_write_reg(priv, 0x53, 0x0f); m88tc6800_write_reg(priv, 0x54, 0x00);

        if (priv->config.xtal == 24000U)
            m88tc6800_set_reg_bits(priv, 0x5b, 0x2, 0x3, 0x5);
        else if (priv->config.xtal == 27000U) {
            m88tc6800_set_reg_bits(priv, 0x5b, 0x6, 0x3, 0x5);
            //m88tc6800_set_reg_bits_expand(priv, 0x4e, 0x08, 0x1, 0x7, 0x7);
            uint32_t wait_time_01 = 0;
            //_mt_fe_tn_set_tune_tc6800_cxd2856(priv, 0x79ac9, 0x32, wait_time_01);
            m88tc6800_write_reg(priv, 0x39, 0x77);
            m88tc6800_read_reg(priv, 0x3a, &buf);
            buf = (buf & 0x3fU) | 0x40U;
            m88tc6800_write_reg(priv, 0x39, 0x77);
            m88tc6800_write_reg(priv, 0x3a, buf);
        }

        if (((priv->config.mode - 1U) < 2U) && (priv->config.int_lt > 1U)) {
            //m88tc6800_set_reg_bits_expand(priv, 0x4e, 0x0f, 0x3, 0x5, 0x4);
            //m88tc6800_set_reg_bits_expand(priv, 0x4e, 0x10, 0x1, 0x1, 0x1);
            //m88tc6800_set_reg_bits_expand(priv, 0x4e, 0x11, 0x1, 0x7, 0x4);
            //m88tc6800_set_reg_bits_expand(priv, 0x4e, 0x19, 0x0, 0x1, 0x1);
            m88tc6800_set_reg_bits(priv, 0x46, 0x1, 0x7, 0x7);
            /* Loop-through gain table (96 entries) */
            static const uint8_t lt_gain_table[] = {
                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2e,
                0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x26, 0x26, 0x26,
                0x22, 0x42, 0x42, 0x42, 0x42, 0x42, 0x14, 0x24,
                0x34, 0x34, 0x54, 0x64, 0x74, 0x18, 0x18, 0x28,
                0x28, 0x38, 0x38, 0x38, 0x38, 0x1c, 0x19, 0x29,
                0x29, 0x39, 0x39, 0x1d, 0x2d, 0x3d, 0x2a, 0x3a,
                0x5a, 0x7a, 0x9b, 0xab, 0x9f, 0x8f, 0x87, 0x7b,
                0xa4, 0x92, 0x86, 0xa6, 0x9e, 0x93, 0x8b, 0x83,
                0x7b, 0x76, 0x71, 0xa5, 0xa2, 0x97, 0x8c, 0x82,
                0x77, 0xa3, 0x93, 0x83, 0x99, 0x75, 0xa0, 0x89,
                0xa1, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            };
            for (int i = 0; i < (int)(sizeof(lt_gain_table)); i++)
                m88tc6800_write_reg(priv, 0x47, lt_gain_table[i]);

            m88tc6800_write_reg(priv, 0x45, 0x1d);
            m88tc6800_write_reg(priv, 0x40, 0x1a);
            m88tc6800_write_reg(priv, 0x41, 0x00);
            m88tc6800_write_reg(priv, 0x39, 0x00);
            m88tc6800_write_reg(priv, 0x3a, 0x00);
            m88tc6800_write_reg(priv, 0x60, 0x34);
            uint32_t wait_time_00 = 0;
            //_mt_fe_tn_set_tune_tc6800_cxd2856(priv, 0x79950, 0xc8, wait_time_00);
            m88tc6800_set_reg_bits(priv, 0x3e, 0x0, 0x7, 0x7);
        }

        m88tc6800_write_reg(priv, 0x45, 0x5d);

        m88tc6800_set_reg_bits(priv, 0x3c, 0x1, 0x7, 0x7);
    } else {
        m88tc6800_write_reg(priv, 0x45, 0x5d);
    }

    /* ------------------------------------------------------------------
     * Main tuning sequence.
     * ------------------------------------------------------------------ */
    m88tc6800_write_reg(priv, 0x04, 0x7f);
    m88tc6800_write_reg(priv, 0x05, 0xd8);
    m88tc6800_preset(priv);

    m88tc6800_set_rf_frontend(priv, freq_KHz);
    m88tc6800_write_reg(priv, 0x05, 0xf8);
    m88tc6800_set_mixer(priv, freq_KHz, m88tc6800_get_mixer_type(priv, freq_KHz));
    m88tc6800_set_lo(priv, freq_KHz, m88tc6800_get_mixer_type(priv, freq_KHz));
    m88tc6800_set_pll(priv);
    m88tc6800_set_bandwidth(priv, bandwidth_hz);

    m88tc6800_write_reg(priv, 0x04, 0x00);
    m88tc6800_write_reg(priv, 0x05, 0x00);

    /* ------------------------------------------------------------------
     * Post-tune loop-through path configuration.
     * This block is disabled (guarded by if(false)) in the original.
     * The loop-through calibration and gain-word computation it contained
     * has been omitted; only the register writes that unconditionally
     * follow it are preserved.
     * ------------------------------------------------------------------ */
    /* if (false) { ... loop-through calibration ... } */

    m88tc6800_set_dac(priv, freq_KHz, bandwidth_hz);

    m88tc6800_write_reg(priv, 0xc9,
                (application & 0xfdU) == 1U ? 0x15U : 0x05U);
    m88tc6800_write_reg(priv, 0x40, 0x1a);
    m88tc6800_write_reg(priv, 0x41, 0x00);

    if (priv->config.xtal == 24000U)
        m88tc6800_write_reg(priv, 0x44, 0x22);
    else if (priv->config.xtal == 27000U)
        m88tc6800_write_reg(priv, 0x44, 0x2a);

    m88tc6800_write_reg(priv, 0x60, 0x34);

    /* Optional loop-through path enable */
    if (((priv->config.mode - 1U) < 2U) && (priv->config.int_lt > 1U)) {
        m88tc6800_read_reg(priv, 0x9a, &lt_buf);
        lt_buf |= 0x10U;
        m88tc6800_write_reg(priv, 0x9a, lt_buf);
    }

    m88tc6800_write_reg(priv, 0x05, 0x04);
    m88tc6800_write_reg(priv, 0xc2, 0x01);
    m88tc6800_write_reg(priv, 0x00, 0x01);
    m88tc6800_write_reg(priv, 0x00, 0x00);
    m88tc6800_write_reg(priv, 0xc2, 0x00);
    m88tc6800_write_reg(priv, 0x05, 0x00);
    m88tc6800_write_reg(priv, 0x39, 0x00);
    m88tc6800_write_reg(priv, 0x3a, 0x00);

    /* ------------------------------------------------------------------
     * Loop-through post-calibration and mode register (reg 0x0d).
     *
     * When mode is 1 or 2 AND int_lt >= 2:
     *   Clear the loop-through enable bit in 0x9a.
     *   If int_lt == 2 exactly: write 0xfd=0x1a, read/mask 0x8b, write back.
     *     Then read 0x9a, conditionally write 0x1c.
     *   If int_lt > 2: read 0x9a directly, conditionally write 0x1c.
     *   For mode == 2: write 0x0d=0xcc; otherwise 0x0d=0xc4.
     * All other paths: write 0x0d=0xc4.
     * ------------------------------------------------------------------ */
    if (((priv->config.mode - 1U) < 2U) && (priv->config.int_lt >= 2U)) {
        lt_buf &= 0xefU;
        m88tc6800_write_reg(priv, 0x9a, lt_buf);

        if ((priv->config.mode - 1U) <= 1U) {
            if (priv->config.int_lt == 2U) {
                m88tc6800_write_reg(priv, 0xfd, 0x1a);
                m88tc6800_read_reg(priv, 0x8b, &lna_buf);
                lna_buf &= 0x77U;
                if (priv->config.custom_cfg == 1U)
                    lna_buf = 0xaa;
                m88tc6800_write_reg(priv, 0x8b, lna_buf);

                /* Fall through to the 0x9a/0x1c block below */
            }
            /* Both int_lt==2 (after writing 0x8b) and int_lt>2
             * reach the same 0x9a read + 0x1c conditional write. */
            m88tc6800_read_reg(priv, 0x9a, &app_buf);
            app_buf &= 0x0fU;
            if (app_buf >= 10U)
                m88tc6800_write_reg(priv, 0x1c, 0x93);
            else if (app_buf < 4U)
                m88tc6800_write_reg(priv, 0x1c, 0x43);
        }

        if (priv->config.mode == 2U)
            m88tc6800_write_reg(priv, 0x0d, 0xcc);
        else
            m88tc6800_write_reg(priv, 0x0d, 0xc4);
    } else {
        m88tc6800_write_reg(priv, 0x0d, 0xc4);
    }

    m88tc6800_write_reg(priv, 0x3d, 0xfe);

    /* ------------------------------------------------------------------
     * Spur / image frequency detection.
     * Read the current VCO frequency from regs 0x4a/0x4b/0x4c, scale
     * to kHz, and check for proximity to harmonics.  If within 20 MHz
     * of a harmonic write reg 0x10=0x50.
     * ------------------------------------------------------------------ */
    m88tc6800_read_reg(priv, 0x4a, &app_buf);
    uint32_t tmp  = (uint32_t)app_buf & 0x0fU;
    m88tc6800_read_reg(priv, 0x4b, &app_buf);
    uint32_t tmp2 = (uint32_t)app_buf;
    m88tc6800_read_reg(priv, 0x4c, &app_buf);
    uint32_t shift = ((uint32_t)app_buf << 25) >> 27;
    app_buf = (uint8_t)shift;
    tmp2 = (tmp2 + tmp * 0x100U) >> shift;

    uint32_t vco_khz = tmp2 * 8U;
    if (priv->config.xtal == 27000U)
        vco_khz = (tmp2 * 0xd8U) / 0x18U;

    if (((vco_khz * 1000U - freq_KHz < 20001U) ||
         (freq_KHz + vco_khz * (uint32_t)-1000 < 20001U)) ||
        ((vco_khz * 1000U + freq_KHz * (uint32_t)-3 < 20001U) ||
         (freq_KHz * 3U + vco_khz * (uint32_t)-1000 < 20001U)))
        m88tc6800_write_reg(priv, 0x10, 0x50);

    m88tc6800_write_reg(priv, 0x66, 0x48);
    m88tc6800_write_reg(priv, 0xb0, 0x0b);

    /* ------------------------------------------------------------------
     * Application-specific AGC filter coefficient tables.
     *
     * LAB_0008d1cc / LAB_0008c440 elimination:
     * The original application==1 block jumped to LAB_0008d1cc which
     * was the start of the application-in-{3,4} block's trailing check.
     * Both blocks now end with the same inline conditional:
     *   application==3 → write 0x60=0xb7
     *   otherwise      → write 0x60=0x34
     * ------------------------------------------------------------------ */
    uint8_t app_val = (uint8_t)application;

    if ((application - 3U) < 2U) {
        /* ISDB-T / DVB-C */
        m88tc6800_write_reg(priv, 0x39, 0x11); m88tc6800_write_reg(priv, 0x3a, 0x18);
        m88tc6800_write_reg(priv, 0x39, 0x12); m88tc6800_write_reg(priv, 0x3a, 0x6a);
        m88tc6800_write_reg(priv, 0x39, 0x15); m88tc6800_write_reg(priv, 0x3a, 0x01);
        m88tc6800_write_reg(priv, 0x39, 0x16); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x17); m88tc6800_write_reg(priv, 0x3a, 0x35);
        m88tc6800_write_reg(priv, 0x39, 0x18); m88tc6800_write_reg(priv, 0x3a, 0x01);
        m88tc6800_write_reg(priv, 0x39, 0x19); m88tc6800_write_reg(priv, 0x3a, 0x18);
        m88tc6800_write_reg(priv, 0x39, 0x05); m88tc6800_write_reg(priv, 0x3a, 0x08);
        m88tc6800_write_reg(priv, 0x39, 0x06); m88tc6800_write_reg(priv, 0x3a, 0x4e);
        m88tc6800_write_reg(priv, 0x39, 0x09); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x0a); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x0b); m88tc6800_write_reg(priv, 0x3a, 0x27);
        m88tc6800_write_reg(priv, 0x39, 0x0c); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x0d); m88tc6800_write_reg(priv, 0x3a, 0x08);
        m88tc6800_write_reg(priv, 0x4e, 0x29); m88tc6800_write_reg(priv, 0x4f, 0xae);
        m88tc6800_write_reg(priv, 0x4e, 0x2c); m88tc6800_write_reg(priv, 0x4f, 0x09);
        m88tc6800_write_reg(priv, 0x4e, 0x2f); m88tc6800_write_reg(priv, 0x4f, 0x08);
        m88tc6800_write_reg(priv, 0x4e, 0x29); m88tc6800_write_reg(priv, 0x4f, 0xee);

        m88tc6800_write_reg(priv, 0x60,
                    application == 3U ? 0xb7U : 0x34U);
    } else if (application == 1U) {
        /* DVB-T */
        m88tc6800_write_reg(priv, 0x39, 0x11); m88tc6800_write_reg(priv, 0x3a, 0x3f);
        m88tc6800_write_reg(priv, 0x39, 0x12); m88tc6800_write_reg(priv, 0x3a, 0x0b);
        m88tc6800_write_reg(priv, 0x39, 0x15); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x16); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x17); m88tc6800_write_reg(priv, 0x3a, 0x05);
        m88tc6800_write_reg(priv, 0x39, 0x18); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x19); m88tc6800_write_reg(priv, 0x3a, 0x7f);
        m88tc6800_write_reg(priv, 0x39, 0x05); m88tc6800_write_reg(priv, 0x3a, 0x3f);
        m88tc6800_write_reg(priv, 0x39, 0x06); m88tc6800_write_reg(priv, 0x3a, 0x03);
        m88tc6800_write_reg(priv, 0x39, 0x09); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x0a); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x0b); m88tc6800_write_reg(priv, 0x3a, app_val);
        m88tc6800_write_reg(priv, 0x39, 0x0c); m88tc6800_write_reg(priv, 0x3a, 0x00);
        m88tc6800_write_reg(priv, 0x39, 0x0d); m88tc6800_write_reg(priv, 0x3a, 0x7f);
        m88tc6800_write_reg(priv, 0x4e, 0x29); m88tc6800_write_reg(priv, 0x4f, 0x8c);
        m88tc6800_write_reg(priv, 0x4e, 0x2c); m88tc6800_write_reg(priv, 0x4f, 0x20);
        m88tc6800_write_reg(priv, 0x4e, 0x2f); m88tc6800_write_reg(priv, 0x4f, 0x02);
        m88tc6800_write_reg(priv, 0x4e, 0x29); m88tc6800_write_reg(priv, 0x4f, 0xcc);

        /* application==1 (DVB-T) never has application==3, so always 0x34 */
        m88tc6800_write_reg(priv, 0x60, 0x34);
    } else {
        /* All other applications (0, 2, …) */
        m88tc6800_write_reg(priv, 0x60, 0x34);
    }
    return 0;
}

static uint32_t xm_list_dBm[] = {
       0x0,           0x0,         0x25A,         0x3BA,
     0x4B4,         0x576,         0x614,         0x69A,
     0x70E,         0x774,         0x7D0,         0x823,
     0x86E,         0x8B4,         0x8F4,         0x930,
     0x968,         0x99D,         0x9CF,         0x9FE,
     0xA2A,         0xA54,         0xA7D,         0xAA3,
     0xAC8,         0xAEC,         0xB0E,         0xB2F,
     0xB4E,         0xB6D,         0xB8A,         0xBA7,
     0xBC2,         0xBDD,         0xBF7,         0xC10,
     0xC29,         0xC40,         0xC58,         0xC6E,
     0xC84,         0xC9A,         0xCAE,         0xCC3,
     0xCD7,         0xCEA,         0xCFE,         0xD10,
     0xD22,         0xD34,         0xD46,         0xD57,
     0xD68,         0xD79,         0xD89,         0xD99,
     0xDA8,         0xDB8,         0xDC7,         0xDD6,
     0xDE4,         0xDF3,         0xE01,         0xE0F,
     0xE1C,         0xE2A,         0xE37,         0xE44,
     0xE51,         0xE5E,         0xE6A,         0xE77,
     0xE83,         0xE8F,         0xE9A,         0xEA6,
     0xEB2,         0xEBD,         0xEC8,         0xED3,
     0xEDE,         0xEE9,         0xEF4,         0xEFE,
     0xF09,         0xF13,         0xF1D,         0xF27,
     0xF31,         0xF3B,         0xF44,         0xF4E,
     0xF58,         0xF61,         0xF6A,         0xF73,
     0xF7D,         0xF86,         0xF8E,         0xF97,
     0xFA0,         0xFA9,         0xFB1,         0xFBA,
     0xFC2,         0xFCA,         0xFD3,         0xFDB,
     0xFE3,         0xFEB,         0xFF3,         0xFFB,
    0x1002,        0x100A,        0x1012,        0x1019,
    0x1021,        0x1028,        0x1030,        0x1037,
    0x103E,        0x1046,        0x104D,        0x1054,
    0x105B,        0x1062,        0x1069,        0x1070,
    0x1076,        0x107D,        0x1084,        0x108B,
    0x1091,        0x1098,        0x109E,        0x10A5,
    0x10AB,        0x10B1,        0x10B8,        0x10BE,
    0x10C4,        0x10CA,        0x10D1,        0x10D7,
    0x10DD,        0x10E3,        0x10E9,        0x10EF,
    0x10F5,        0x10FA,        0x1100,        0x1106,
    0x110C,        0x1111,        0x1117,        0x111D,
    0x1122,        0x1128,        0x112D,        0x1133,
    0x1138,        0x113E,        0x1143,        0x1148,
    0x114E,        0x1153,        0x1158,        0x115D,
    0x1163,        0x1168,        0x116D,        0x1172,
    0x1177,        0x117C,        0x1181,        0x1186,
    0x118B,        0x1190,        0x1195,        0x119A,
    0x119F,        0x11A3,        0x11A8,        0x11AD,
    0x11B2,        0x11B6,        0x11BB,        0x11C0,
    0x11C4,        0x11C9,        0x11CE,        0x11D2,
    0x11D7,        0x11DB,        0x11E0,        0x11E4,
    0x11E9,        0x11ED,        0x11F1,        0x11F6,
    0x11FA,        0x11FE,        0x1203,        0x1207,
    0x120B,        0x1210,        0x1214,        0x1218,
    0x121C,        0x1220,        0x1224,        0x1229,
    0x122D,        0x1231,        0x1235,        0x1239,
    0x123D,        0x1241,        0x1245,        0x1249,
    0x124D,        0x1251,        0x1255,        0x1259,
    0x125C,        0x1260,        0x1264,        0x1268,
    0x126C,        0x1270,        0x1273,        0x1277,
    0x127B,        0x127F,        0x1282,        0x1286,
    0x128A,        0x128D,        0x1291,        0x1295,
    0x1298,        0x129C,        0x12A0,        0x12A3,
    0x12A7,        0x12AA,        0x12AE,        0x12B1,
    0x12B5,        0x12B8,        0x12BC,        0x12BF,
    0x12C3,        0x12C6,        0x12CA,        0x12CD
};

/* Refactored from Ghidra decompilation of TC6800_GetRFStrength.
 *
 * Variable name mapping from decompilation:
 *   uVar1        -> freq        (priv->tuner_freq, kHz)
 *   uVar2        -> gain_raw    (raw byte from reg 0x63, the gain ADC)
 *   iVar4        -> gain_x10    (gain_raw * 10 + band_offset; only used when
 *                                reg 0x8b state == 0x55 to compute level)
 *   iVar3        -> level       (signal level estimate in units of 0.1 dBm;
 *                                accumulated through phase 1 and phase 2)
 *   local_31[0]  -> reg_val     (single-byte read buffer reused for reg 0x63
 *                                and reg 0x8b; after the 0x8b read it is
 *                                masked with 0x77 as an LNA/att state code)
 *   bVar5        -> apply_adj   (flag for the DVB-T high-band adjustment;
 *                                effectively dead code — see comment below)
 *   extraout_r1  -> pRfStrength (Ghidra artefact: equals the parameter directly)
 *
 * Frequency band boundaries (kHz):
 *   0x01adb1 =  110,001   0x0518b1 =  334,001   0x073b91 =  474,001
 *   0x030d41 =  200,001   0x0595b1 =  366,001   0x0927c1 =  600,001
 *   0x061a81 =  400,001   0x0aae61 =  700,001   0x0c3501 =  800,001
 *   0x0d1791 =  858,001   0x0dbba1 =  900,001
 *
 * LNA/attenuator state codes (reg 0x8b & 0x77):
 *   0x55  -> LNA + attenuator both active
 *   0x11  -> LNA stage only
 *   other -> default (no level adjustment)
 */
int m88tc6800_get_rf_power(struct m88tc6800_priv *priv, int32_t *strength)
{
    uint32_t freq = priv->frequency_hz / 1000;
    uint8_t  reg_val;
    int32_t  gain_x10;
    int32_t  level;
    bool     need_lna_adjust;
    uint32_t application = 0;

    /* ------------------------------------------------------------------
     * Phase 1: read gain ADC (reg 0x63) and LNA/attenuator state
     * (reg 0x8b, masked 0x77), then produce a first-order level estimate
     * in units of 0.1 dBm.
     *
     * gain_x10 is computed alongside level for the bands that need it;
     * it is only consumed when the LNA/att state is 0x55, in which case
     * level = gain_x10 + 0x82 (overriding the initial level value).
     *
     * The fixed-offset UHF bands [200001..800000] all share the pattern:
     *   gain_x10 = gain_raw * 10 + band_offset
     *   level    = gain_x10 + 0x96
     * with only the offset differing per sub-band.
     *
     * Bands >= 900001 read reg 0x8b but do NOT apply the LNA correction —
     * need_lna_adjust is false for those paths.
     * ------------------------------------------------------------------ */

    if (freq < 0x1adb1U) {
        /* VHF-low / MF  (< 110,001 kHz) */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        gain_x10        = (int32_t)(reg_val * 10U) - 0x1d1;
        level           = (int32_t)(reg_val * 10U) - 0x13b;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val        &= 0x77U;
        need_lna_adjust = true;

    } else if (freq < 0x30d41U) {
        /* VHF-high  (110,001 .. 200,000 kHz) */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        gain_x10 = (int32_t)(reg_val * 10U); /* base; offset applied below */
        level    = gain_x10 - 300;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val &= 0x77U;
        if (reg_val == 0x55U) {
            /* 0x55 case is fully resolved here; no further lna check */
            level           = gain_x10 - 0x140;
            need_lna_adjust = false;
        } else {
            /* gain_x10 is not used by the 0x11 branch — leave it set
             * but flag that only the 0x11 sub-case is still pending   */
            need_lna_adjust = true;
        }

    } else if (freq < 0x518b1U) {
        /* UHF low-A  (200,001 .. 334,000 kHz) */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        gain_x10        = (int32_t)(reg_val * 10U) - 0x1ae;
        level           = gain_x10 + 0x96;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val        &= 0x77U;
        need_lna_adjust = true;

    } else if (freq < 0x61a81U) {
        /* UHF low-B  (334,001 .. 400,000 kHz) */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        gain_x10        = (int32_t)(reg_val * 10U) - 0x1ea;
        level           = gain_x10 + 0x96;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val        &= 0x77U;
        need_lna_adjust = true;

    } else if (freq < 0x927c1U) {
        /* UHF mid-A  (400,001 .. 600,000 kHz) */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        gain_x10        = (int32_t)(reg_val * 10U) - 0x1d6;
        level           = gain_x10 + 0x96;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val        &= 0x77U;
        need_lna_adjust = true;

    } else if (freq < 0xaae61U) {
        /* UHF mid-B  (600,001 .. 700,000 kHz) */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        gain_x10        = (int32_t)(reg_val * 10U) - 0x1c7;
        level           = gain_x10 + 0x96;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val        &= 0x77U;
        need_lna_adjust = true;

    } else if (freq <= 800000U) {
        /* UHF mid-C  (700,001 .. 800,000 kHz) */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        gain_x10        = (int32_t)(reg_val * 10U) - 0x1c2;
        level           = gain_x10 + 0x96;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val        &= 0x77U;
        need_lna_adjust = true;

    } else if (freq < 0xdbba1U) {
        /* UHF high  (800,001 .. 900,000 kHz) — asymmetric offsets */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        gain_x10        = (int32_t)(reg_val * 10U) - 0x1cc;
        level           = (int32_t)(reg_val * 10U) - 0x136;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val        &= 0x77U;
        need_lna_adjust = true;

    } else {
        /* UHF top  (>= 900,001 kHz) — reg 0x8b is read but not used */
        m88tc6800_read_reg(priv, 0x63, &reg_val);
        level           = (int32_t)(int16_t)(uint16_t)reg_val * 10 - 0x154;
        m88tc6800_read_reg(priv, 0x8b, &reg_val);
        reg_val        &= 0x77U;
        need_lna_adjust = false;
    }

    /* ------------------------------------------------------------------
     * LNA/attenuator state correction.
     *
     * reg 0x8b masked with 0x77 encodes the active gain stages:
     *   0x55 → both LNA + attenuator: level = gain_x10 + 0x82
     *   0x11 → LNA only:              level -= frequency-dependent offset
     *   other → no change
     * ------------------------------------------------------------------ */
    if (need_lna_adjust) {
        if (reg_val == 0x55U) {
            level = gain_x10 + 0x82;
        } else if (reg_val == 0x11U) {
            level += (freq < 0xc3501U) ? -0x28 : -0x19;
        }
    }

    /* ------------------------------------------------------------------
     * Phase 2: per-band correction added to level.
     *
     * All paths not explicitly listed below fall through and add +0x3c.
     *
     * application == 0 (auto/scan):
     *   freq in [366,001..374,000]          +0x3c  (default fallthrough)
     *   freq in [480,000..491,999]          +0x32
     *   freq in [610,000..624,000]          +0x3c  (default fallthrough)
     *   freq in [800,000..820,000]          +10
     *   all other ranges                    no addition
     *
     * application != 0 (broadcast standards):
     *   freq in [334,001..400,000]          +0x3c  (default fallthrough)
     *   freq in [400,001..474,000]          +0x32
     *   freq in [474,001..600,000)    ─┐
     *   freq in [600,001..800,000]     ├─  +0x41
     *   freq in [800,001..858,000]    ─┘
     *   freq in [858,001..900,000]          +10
     *   freq in [900,001..1,019,999]        +0xf
     *   freq >= 1,020,000:                  -0x1e if application==1
     *                                       (freq==110,000 branch is dead
     *                                        code; freq cannot be both
     *                                        >= 900,001 and == 110,000)
     *   all other ranges (< 334,001)        +0x3c  (default fallthrough)
     *
     * The unsigned subtraction trick: (a - b) < c  is true for both
     * a in [b .. b+c-1] AND wraps when a < b (making the result huge).
     * This is the compiler's idiom for range checks on unsigned values.
     * ------------------------------------------------------------------ */
    if (application == 0x0U) {
        if ((freq - 0x595b1U) > 7999U) {
            /* freq outside [366,001..374,000] */
            if ((freq - 480000U) < 0x2ee1U) {
                level += 0x32;                          /* [480,000..491,999] */
            } else if ((freq - 610000U) <= 14000U) {
                level += 0x3c;                          /* [610,000..624,000] */
            } else if ((freq - 800000U) <= 20000U) {
                level += 10;                            /* [800,000..820,000] */
            }
            /* else: no addition */
        } else {
            level += 0x3c;                              /* [366,001..374,000] */
        }
    } else if ((freq - 0x518b1U) > 65999U) {
        /* freq outside [334,001..400,000] */
        if ((freq - 0x61a81U) <= 73999U) {
            level += 0x32;                              /* [400,001..474,000] */
        } else if (((freq - 0x73b91U) < 0x1ec30U) ||
               ((freq - 0x927c1U) < 200000U)   ||
               ((freq - 0xc3501U) < 58000U)) {
            level += 0x41;  /* [474,001..600,000) ∪ [600,001..800,000] ∪ [800,001..858,000] */
        } else if ((freq - 0xd1791U) <= 41999U) {
            level += 10;                                /* [858,001..900,000] */
        } else if ((freq - 0xdbba1U) < 120000U) {
            level += 0xf;                               /* [900,001..1,019,999] */
        } else {
            /* freq >= 1,020,000 kHz.
             * The (freq == 110000) check is dead code here since freq
             * is >= 1,020,000. The (freq < 0x1adb1) guard is also dead.
             * Only the application == 1 check is reachable.             */
            if (application == 0x1U)
                level += -0x1e;
        }
    } else {
        level += 0x3c;                                      /* [334,001..400,000] */
    }

    /* ------------------------------------------------------------------
     * Phase 3: final RF level calculation.
     *
     * Read power-detector index register 0xc8, look up the calibrated
     * dBm value from the xm_list_dBm table, subtract the accumulated
     * level estimate, and scale to dBm.  Clamp to -107 dBm minimum.
     * ------------------------------------------------------------------ */
    m88tc6800_read_reg(priv, 0xc8, &reg_val);
    int32_t rf_level = (int32_t)((xm_list_dBm[reg_val] / 10 - 0x1a9) - level) / 10;
    int32_t result   = (rf_level > -0x6c) ? rf_level : -0x6b;

    *strength = result;

    return 0;
}
