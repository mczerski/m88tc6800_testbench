#include "m88tc6800_priv.h"


struct m88tc6800_priv priv = {
    .config = {
        .xtal = 27000,
        .xtal_cap = 0x18,
        .dac_gain = 2,
        .dac = 4570
    }
};

int m88tc6800_write_reg(struct m88tc6800_priv *priv, u8 reg, u8 val)
{
    uint32_t actual_op = ('w' << 24) + (reg << 8) + val;
    uint32_t expected_op = i2c_log[actual_i2c_op];
    if (actual_op != expected_op) {
        printf("op: %d, actual: %08x, expected: %08x\n", actual_i2c_op, actual_op, expected_op);
        printf("%s", msg);
        exit(-1);
    }
    actual_i2c_op++;
    return 0;
}

int m88tc6800_read_reg(struct m88tc6800_priv *priv, u8 reg, u8 *val)
{
    *val = i2c_reg[reg];
    uint32_t actual_op = ('r' << 24) + (reg << 8) + *val;
    uint32_t expected_op = i2c_log[actual_i2c_op];
    if (actual_op != expected_op) {
        printf("op: %d, actual: %08x, expected: %08x\n", actual_i2c_op, actual_op, expected_op);
        printf("%s", msg);
        exit(-1);
    }
    actual_i2c_op++;
    return 0;
}
