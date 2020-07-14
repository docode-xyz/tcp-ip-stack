#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
void util_apply_mask(const char *prefix, const char mask, char *str_prefix);

void util_l2_fill_mac_broadcast(uint8_t *mac_arr);

#endif