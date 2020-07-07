#include "common.h"

void dump_interface(const interface_t *interface) {
  assert(interface && "MSG: Failed to dump interface; interface is NULL");

  link_t *link = interface->link;
  node_t *nbr = graph_get_nbr_node(interface);

  printf("Interface name: %s\n", interface->if_name);
  printf("\tNbr node: %s, Local node: %s, Cost: %u\n", nbr->node_name,
         interface->att_node->node_name, link->cost);
}