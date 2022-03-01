#ifndef HAL_NDK_H
#define HAL_NDK_H

#include <stdint.h>

int load_module(const char* module_id, const struct hw_module_t** hw_module);
int check_bit(uint32_t n, int k);
void print_module_info(const struct hw_module_t** hw_module);

#endif