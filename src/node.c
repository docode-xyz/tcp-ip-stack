#include "common.h"

node_t *node_create_new(const char *name) {
  node_t *new_node = calloc(1, sizeof(node_t));
  if (!new_node) {
    fprintf(stderr, "%s", "[ERROR]: Failed to create a new node!\n");
    return NULL;
  }

  if (strlen(name) == 0)
    strncpy(new_node->node_name, "NODE: DEF NAME", NODE_NAME_LEN);
  else
    strncpy(new_node->node_name, name, NODE_NAME_LEN);

  new_node->node_name[NODE_NAME_LEN - 1] = '\0';

  glist_init(&new_node->graph_node);

  return new_node;
}

bool node_set_lb_addr(node_t *node, const char *lb_addr) {
  assert(lb_addr && "MSG: Incorrect loopback address!");

  strncpy(NODE_LOOPBACK_ADDR(node), lb_addr, IP_ADDR_LEN);
  NODE_LOOPBACK_ADDR(node)[IP_ADDR_LEN - 1] = '\0';

  node->net_node_prop.is_loopback_addr_config = true;

  return true;
}

interface_t *node_get_iface_by_name(const node_t *node,
                                    const char *iface_name) {
  assert(iface_name && "MSG: Incorrect interface name!");

  interface_t *iface = NULL;
  for (size_t i = 0; i < MAX_IF_PER_NODE; i++) {
    iface = node->if_arr[i];
    if (!strcmp(iface->if_name, iface_name)) {
      return iface;
    }
  }
  return NULL;
}

bool node_set_iface_ip_addr(node_t *node, const char *local_iface,
                            const char *ip_addr, const char mask) {
  assert(local_iface && "MSG: Incorrect local interface!");
  assert(ip_addr && "MSG: Incorrect IP address!");

  interface_t *iface = node_get_iface_by_name(node, local_iface);
  assert(iface);

  strncpy(IFACE_IP(iface), ip_addr, IP_ADDR_LEN);
  IFACE_IP(iface)[IP_ADDR_LEN - 1] = '\0';

  iface->net_iface_prop.mask = mask;
  iface->net_iface_prop.is_ip_addr_config = true;

  return true;
}

bool node_unset_iface_ip_addr(node_t *node, const char *local_iface) {
  assert(local_iface && "MSG: Incorrect local interface!");

  interface_t *iface = node_get_iface_by_name(node, local_iface);
  assert(iface);

  memset(IFACE_IP(iface), 0, IP_ADDR_LEN);
  iface->net_iface_prop.is_ip_addr_config = false;

  return true;
}

void dump_node(const node_t *node) {
  assert(node && "MSG: Failed to dump a node: node is NULL");

  printf("Node name: %s\n", node->node_name);

  interface_t *iface = NULL;
  for (size_t i = 0; i < MAX_IF_PER_NODE; i++) {
    iface = node->if_arr[i];

    if (!iface) break;

    dump_interface(iface);
  }
}