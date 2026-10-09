#include "common.h"
#include "original.h"
#include "new.h"

/* The two bit-field helpers, exhaustively.
 *
 * These are worth a runner of their own for two reasons. First,
 * m88tc6800_set_reg_bits is a genuine reimplementation -- it builds the
 * mask as ((1 << (end - begin + 1)) - 1) << begin where the original uses
 * (0xff << x) >> y -- yet the driver only ever calls it with about a
 * dozen distinct (begin, end) pairs, so most of the mask space was never
 * compared. Second, the argument order is reversed between the two: the
 * rewrite takes (begin, end) and the original takes (high, low), and
 * every ported call site happens to use either begin == end or a pair the
 * original sorts anyway, so a swap would not have shown up.
 *
 * begin > end is deliberately not tested: the original sorts its two bit
 * arguments, but the rewrite's (1 << (end - begin + 1)) shifts by a
 * negative amount there, which is undefined rather than merely different.
 */
int main() {
    suite_init();

    uint8_t reg_list[] = {0x00, 0x0b, 0x13, 0x20, 0x3c, 0x53, 0xa7, 0xff};

    for (unsigned pattern = 0; pattern < n_patterns; pattern++) {
        for (int r = 0; r < sizeof(reg_list); r++) {
            for (uint32_t begin = 0; begin < 8; begin++) {
                for (uint32_t end = begin; end < 8; end++) {
                    for (uint32_t val = 0; val < 256; val++) {
                        init();
                        i2c_reg_fill(pattern);
                        sprintf(msg, "set_reg_bits reg: %02x, val: %02x, begin: %d, end: %d, background: %02x\n",
                                reg_list[r], val, begin, end, i2c_reg[reg_list[r]]);
                        _mt_fe_tn_set_reg_bit_tc6800_cxd2856(reg_list[r], val, end, begin);
                        m88tc6800_set_reg_bits(&priv, reg_list[r], val, begin, end);
                        finish();
                    }
                }
            }
        }
    }
    printf("reg_bits OK\n");
}
