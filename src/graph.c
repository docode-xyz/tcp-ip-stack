#include <stdlib.h>
#include <string.h>

#include "common.h"

graph_t *graph_create_new(const char *graph_name) {
  graph_t *new_graph = calloc(1, sizeof(graph_t));
  if (!new_graph) {
    fprintf(stderr, "%s", "[ERROR]: Failed to create a new graph!\n");
    return NULL;
  }

  if (strlen(graph_name) == 0)
    strncpy(new_graph->topology_name, "GRAPH: DEF NAME", TOPOLOGY_NAME_LEN);
  else
    strncpy(new_graph->topology_name, graph_name, TOPOLOGY_NAME_LEN);

  new_graph->topology_name[TOPOLOGY_NAME_LEN - 1] = '\0';

  glist_init(&new_graph->node_list);

  return new_graph;
}

node_t *graph_create_node(graph_t *graph, char *name) {
  assert(graph && "MSG: graph is NULL");

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
  glist_push_right(&graph->node_list, &new_node->graph_node);

  return new_node;
}

void graph_insert_link_btw_2_nodes(node_t *node_from, node_t *node_to,
                                   char *from_if_name, char *to_if_name,
                                   uint32_t cost) {
  link_t *new_link = calloc(1, sizeof(link_t));
  if (!new_link) {
    fprintf(stderr, "%s", "[ERROR]: Failed to create a new link!\n");
    return;
  }

  strncpy(new_link->if_from.if_name, from_if_name, INTERFACE_NAME_LEN);
  new_link->if_from.if_name[INTERFACE_NAME_LEN - 1] = '\0';
  strncpy(new_link->if_to.if_name, to_if_name, INTERFACE_NAME_LEN);
  new_link->if_to.if_name[INTERFACE_NAME_LEN - 1] = '\0';

  /* Set a back pointer */
  new_link->if_from.link = new_link;
  new_link->if_to.link = new_link;

  new_link->if_from.att_node = node_from;
  new_link->if_to.att_node = node_to;
  new_link->cost = cost;

  /* Plug-in interface */
  int32_t avaliable_slot_idx = node_get_if_avaliable_slot(node_from);
  if (avaliable_slot_idx == -1) {
    fprintf(stderr, "[ERROR]: There is no avaliable slot in the %s node!\n",
            node_from->node_name);
    return;
  }
  node_from->if_arr[avaliable_slot_idx] = &new_link->if_from;

  avaliable_slot_idx = node_get_if_avaliable_slot(node_to);
  if (avaliable_slot_idx == -1) {
    fprintf(stderr, "[ERROR]: There is no avaliable slot in the %s node!\n",
            node_to->node_name);
    return;
  }
  node_to->if_arr[avaliable_slot_idx] = &new_link->if_to;
}

void dump_graph(const graph_t *graph) {
  assert(graph && "MSG: Failed to dump a graph; graph is NULL");

  printf("Topology name: %s\n", graph->topology_name);

  node_t *node = NULL;
  glist_t *glist_ptr = NULL;
  // clang-format off
  ITERATE_GLIST_BEGIN(&graph->node_list, glist_ptr){
      node = graph_glue_to_node(glist_ptr);
      dump_node(node);
  }ITERATE_GLIST_END(&graph->node_list, glist_ptr);
  // clang-format on
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

void dump_interface(const interface_t *interface) {
  assert(interface && "MSG: Failed to dump interface; interface is NULL");

  link_t *link = interface->link;
  node_t *nbr = graph_get_nbr_node(interface);

  printf("Interface name: %s\n", interface->if_name);
  printf("\tNbr node: %s, Local node: %s, Cost: %u\n", nbr->node_name,
         interface->att_node->node_name, link->cost);
}