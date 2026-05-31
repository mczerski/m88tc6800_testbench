#include "common.h"
#include <stdlib.h>
#include <string.h>

uint32_t i2c_log[1000];
uint32_t expected_i2c_op = 0;
uint32_t actual_i2c_op = 0;
uint8_t i2c_reg[256];
char msg[1000];

void init() {
  expected_i2c_op = 0;
  actual_i2c_op = 0;
  memset(msg, 0, sizeof(msg));
}

void finish() {
    if (expected_i2c_op != actual_i2c_op) {
        printf("expected ops: %d, actual ops: %d\n", expected_i2c_op, actual_i2c_op);
        printf("%s", msg);
        exit(-1);
    }
}
