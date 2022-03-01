#ifndef HAL_NDK_H
#define HAL_NDK_H

#include <stdint.h>

int load_hw(const char* module_id, const struct hw_module_t** hw_module);
int checkBit(uint32_t n, int k);

#endif