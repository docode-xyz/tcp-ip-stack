/**
 * @file graph.h
 * @author Valery Ivanov
 * @date 5 Jul 2020
 * @brief Graph model representation
 *
 * Graph - it is a collection of the nodes.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <assert.h>
#include <stdint.h>

#include "../../lib/glist/glist.h"
#include "link/link.h"
#include "node/interface/interface.h"
#include "node/node.h"

#define TOPOLOGY_NAME_LEN 32

/**
 * @brief The Graph model description
 */
typedef struct graph {
  char topology_name[TOPOLOGY_NAME_LEN];
  glist_t node_list;
} graph_t;

GLIST_TO_STRUCT(graph_glue_to_node, node_t, graph_node)

graph_t *graph_create_new(const char *graph_name);

node_t *graph_create_node(graph_t *graph, char *name);

void graph_insert_link_btw_2_nodes(node_t *node_from, node_t *node_to,
                                   char *from_if_name, char *to_if_name,
                                   uint32_t cost);

/**
 * @brief Returns neighbor node
 *
 * @note Should be moved to the separate file: interface.h
 */
static inline node_t *graph_get_nbr_node(const interface_t *interface) {
  assert(interface->att_node);
  assert(interface->link);

  link_t *link = interface->link;
  if (&link->if_from == interface)
    return link->if_to.att_node;
  else
    return link->if_from.att_node;
}

/* Prints routines */

void dump_graph(const graph_t *graph);
void dump_node(const node_t *node);
void dump_interface(const interface_t *interface);

#endif
