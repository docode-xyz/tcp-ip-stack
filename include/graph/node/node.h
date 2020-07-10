/**
 * @file node.h
 * @author Valery Ivanov
 * @date 7 Jul 2020
 * @brief Node representation
 */
#ifndef NODE_H
#define NODE_H

#include "../../../lib/glist/glist.h"
#include "../../net.h"
#include "interface/interface.h"

#define NODE_NAME_LEN 16
#define MAX_IF_PER_NODE 10

/* Forward declaration */
typedef struct interface interface_t;

typedef struct node {
  char node_name[NODE_NAME_LEN];
  interface_t *if_arr[MAX_IF_PER_NODE]; /**< Empty slots on the routing devices;
                                     if NULL it's means that slot is empty  */
  net_node_prop_t net_node_prop;
  glist_t graph_node;
} node_t;

/**
 * @brief Create a new node
 *
 * @return New node or NULL on failure
 */
node_t *node_create_new(const char *name);

/**
 * @brief Configure loopback address of a node
 *
 * @param[IN] node     A node where need to set the loopback address
 * @param[IN] lb_addr  New loopback address
 *
 * @return true on success
 */
bool node_set_lb_addr(node_t *node, const char *lb_addr);

/**
 * @brief Configure the IP address and mask value over the interface of the node
 */
bool node_set_iface_ip_addr(node_t *node, const char *local_iface,
                            const char *ip_addr, const char mask);

/**
 * @brief This function removes an IP address and mask
 *
 * @param[IN] node        The node where need to unset the interface IP address
 * @param[IN] local_iface The name of interface
 *
 * @warning NEGATIVE API
 * 
 * @return true on success
 */
bool node_unset_iface_ip_addr(node_t *node, const char *local_iface);

/**
 * @brief Returns index of avaliable interface slot
 *
 * @return Index of avaliable interface slot
 *         -1 if there is no avaliable slot
 */
inline int32_t node_get_if_avaliable_slot(node_t *node) {
  for (size_t i = 0; i < MAX_IF_PER_NODE; i++) {
    if (node->if_arr[i]) continue;
    return i;
  }
  return -1;
}

interface_t *node_get_iface_by_name(const node_t *node, const char *iface_name);

void dump_node(const node_t *node);

#endif