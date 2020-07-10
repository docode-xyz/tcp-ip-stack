/**
 * @file net.h
 * @author Valery Ivanov
 * @date 7 Jul 2020
 * @brief Commonly definitions for network programming
 *
 */
#ifndef NET_H
#define NET_H

#include <stdbool.h>
#include <stdint.h>

/* Forwarding declaration */
typedef struct arp_table_ arp_table_t;
typedef struct mac_table_ mac_table_t;
typedef struct route_table_ route_table_t;

#define IP_ADDR_LEN 16
typedef struct ip_addr_ {
  char addr[IP_ADDR_LEN];
} __attribute__((packed, aligned(1))) ip_addr_t;

#define MAC_ADDR_LEN 6
typedef struct mac_addr_ {
  char addr[MAC_ADDR_LEN];
} __attribute__((packed, aligned(1))) mac_addr_t;

typedef enum {
  L2_MODE_ACCESS,
  L2_MODE_TRUNK,
  L2_MODE_UNKNOWN,
} E_IFACE_L2_MODE;

char *net_get_iface_l2_mode_str(const E_IFACE_L2_MODE iface_l2_mode);

/**
 * @brief Network NODE properties
 */
typedef struct {
  /* L3 Properties */
  bool is_loopback_addr_config;
  ip_addr_t loopback_addr;

} net_node_prop_t;

static inline void net_node_prop_init(net_node_prop_t *node) {
  node->is_loopback_addr_config = false;
  memset(&node->loopback_addr.addr, 0, IP_ADDR_LEN);
}

/**
 * @brief Network INTERFACE properties
 */
typedef struct {
  /* L2 Properties */
  mac_addr_t mac_addr;

  /* L3 Properties */
  bool is_ip_addr_config;
  ip_addr_t ip_addr;
  uint8_t mask;

} net_iface_prop_t;

#define IFACE_IP(iface_ptr) ((iface_ptr)->net_iface_prop.ip_addr.addr)
#define IFACE_MAC(iface_ptr) ((iface_ptr)->net_iface_prop.mac_addr.addr)
#define NODE_LOOPBACK_ADDR(node_ptr) \
  ((node_ptr)->net_node_prop.loopback_addr.addr)

static inline void net_iface_prop_init(net_iface_prop_t *iface) {
  memset(&iface->mac_addr.addr, 0, MAC_ADDR_LEN);
  iface->is_ip_addr_config = false;
  memset(&iface->ip_addr.addr, 0, IP_ADDR_LEN);
  iface->mask = 0;
}

/* Network NODE properties */

#endif