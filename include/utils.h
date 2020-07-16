#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define IS_BROADCAST_MAC(mac)                                                  \
  (mac[0] == 0xFF && mac[1] == 0xFF && mac[2] == 0xFF && mac[3] == 0xFF &&     \
   mac[4] == 0xFF && mac[5] == 0xFF)

void util_apply_mask(const char *prefix, const char mask, char *str_prefix);

void util_l2_fill_mac_broadcast(uint8_t *mac_arr);

#endif