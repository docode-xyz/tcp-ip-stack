#include "common.h"
#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <stdint.h>
#include <sys/socket.h>

static const uint32_t NETMASK_ANY_ADDR = 32;

void util_apply_mask(const char *prefix, const char mask, char *str_prefix) {
  uint32_t prefix_binary = 0;
  inet_pton(AF_INET, prefix, &prefix_binary);
  prefix_binary = htonl(prefix_binary);

  uint32_t subnet_mask = 0xFFFFFFFF;
  subnet_mask = subnet_mask << (NETMASK_ANY_ADDR - mask);

  prefix_binary = prefix_binary & subnet_mask;

  prefix_binary = htonl(prefix_binary);
  inet_ntop(AF_INET, &prefix_binary, str_prefix, 16);

  str_prefix[IP_ADDR_LEN - 1] = '\0';
}

void util_l2_fill_mac_broadcast(uint8_t *mac_arr) {
  assert(mac_arr);

  mac_arr[0] = 0xFF;
  mac_arr[1] = 0xFF;
  mac_arr[2] = 0xFF;
  mac_arr[3] = 0xFF;
  mac_arr[4] = 0xFF;
  mac_arr[5] = 0xFF;
}
