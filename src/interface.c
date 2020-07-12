#include "common.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>

static uint32_t calc_hash(void *ptr, size_t size) {
  uint32_t value = 0, i = 0;
  char *str = (char *)ptr;
  while (i < size) {
    value += *str;
    value *= 60;
    str++;
    i++;
  }
  return value;
}

void interface_set_mac_addr(interface_t *iface) {
  assert(iface);
  node_t *node = iface->att_node;

  assert(node);
  uint32_t hash = calc_hash(node->node_name, NODE_NAME_LEN);
  hash += calc_hash(iface->if_name, INTERFACE_NAME_LEN);
  memset(IFACE_MAC(iface), hash, sizeof(uint32_t));
}

void dump_interface(const interface_t *interface) {
  assert(interface && "MSG: Failed to dump interface; interface is NULL");

  link_t *link = interface->link;
  node_t *nbr = graph_get_nbr_node(interface);

  printf("Interface name: %s\n", interface->if_name);
  printf("\tNbr node: %s, Local node: %s, Cost: %u\n", nbr->node_name,
         interface->att_node->node_name, link->cost);
}