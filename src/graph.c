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

  node_t *new_node = node_create_new(name);
  assert(new_node);

  glist_push_right(&graph->node_list, &new_node->graph_node);

  return new_node;
}

void graph_insert_link_btw_2_nodes(node_t *node_from, node_t *node_to,
                                   char *from_if_name, char *to_if_name,
                                   uint32_t cost) {
  link_t *new_link = link_create_new(from_if_name, to_if_name, cost);
  assert(new_link);

  /* Set a back pointer */
  new_link->if_from.link = new_link;
  new_link->if_to.link = new_link;

  new_link->if_from.att_node = node_from;
  new_link->if_to.att_node = node_to;

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