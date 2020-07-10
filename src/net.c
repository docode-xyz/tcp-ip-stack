#include "common.h"

static char *iface_l2_str_arr[] = {"MODE ACCES", "MODE TRUNK", "MODE UNKNOWN"};
char *net_get_iface_l2_mode_str(const E_IFACE_L2_MODE iface_l2_mode) {
  return iface_l2_str_arr[iface_l2_mode];
}