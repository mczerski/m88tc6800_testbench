#pragma once
typedef unsigned char   undefined;

//typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned long long    qword;
typedef int    sdword;
typedef long long    sqword;
typedef short    sword;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined3;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined5;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef struct _MT_FE_TN_Device_Settings_TC6800 _MT_FE_TN_Device_Settings_TC6800, *P_MT_FE_TN_Device_Settings_TC6800;

typedef uchar __u8;

typedef __u8 uint8_t;

typedef word __u16;

typedef __u16 uint16_t;

typedef dword __u32;

typedef __u32 uint32_t;

struct _MT_FE_TN_Device_Settings_TC6800 {
    uint8_t tuner_init_OK;
    uint8_t tuner_mcu_status;
    uint8_t tuner_dev_addr;
    uint8_t tuner_application;
    uint16_t tuner_qam;
    uint16_t tuner_mtt;
    uint16_t tuner_custom_cfg;
    uint32_t tuner_version;
    uint8_t tuner_fw_version;
    uint32_t tuner_time;
    uint8_t tuner_crystal_cap;
    uint8_t tuner_clock_out;
    uint16_t tuner_mode;
    uint8_t tuner_int_lt;
    uint8_t tuner_gpio_out;
    uint32_t tuner_freq;
    uint8_t tuner_int_im;
    uint16_t tuner_mixer_type;
    uint32_t tuner_crystal;
    uint32_t tuner_int_ldiv;
    uint32_t tuner_int_fvco_tg;
    uint32_t tuner_dac;
    uint8_t tuner_dac_gain;
    uint32_t tuner_bandwidth;
    uint8_t tuner_signal_delay_en;
    uint32_t tuner_signal_delay_ns;
    uint8_t tuner_harmonic_imp;
};

