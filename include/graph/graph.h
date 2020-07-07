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

#define TOPOLOGY_NAME_LEN 32
#define INTERFACE_NAME_LEN 16
#define NODE_NAME_LEN 16
#define MAX_IF_PER_NODE 10

/*Forward Declarations*/
typedef struct node node_t;
typedef struct link link_t;
typedef struct interface interface_t;

/**
 * @brief The Graph model description
 */
typedef struct graph {
  char topology_name[TOPOLOGY_NAME_LEN];
  glist_t node_list;
} graph_t;

typedef struct node {
  char node_name[NODE_NAME_LEN];
  interface_t *if_arr[MAX_IF_PER_NODE]; /**< Empty slots on the routing devices;
                                     if NULL it's means that slot is empty  */
  glist_t graph_node;
} node_t;

GLIST_TO_STRUCT(graph_glue_to_node, node_t, graph_node)

/**
 * @brief Interface description
 *
 * Each interface contain the name,
 *  owning node and slot to plug-in
 */
typedef struct interface {
  char if_name[INTERFACE_NAME_LEN];
  node_t *att_node; /**< Owning node; To which node related this interface */
  link_t *link;
} interface_t;

/**
 * @brief Wire
 */
typedef struct link {
  interface_t if_from;
  interface_t if_to;
  uint32_t cost;
} link_t;

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

/**
 * @brief Returns index of avaliable interface slot
 *
 * @note Should be moved to the separate file: node.h
 *
 * @return Index of avaliable interface slot
 *         -1 if there is no avaliable slot
 */
static inline int32_t node_get_if_avaliable_slot(node_t *node) {
  for (size_t i = 0; i < MAX_IF_PER_NODE; i++) {
    if (node->if_arr[i]) continue;
    return i;
  }
  return -1;
}

/* Prints routines */

void dump_graph(const graph_t *graph);
void dump_node(const node_t *node);
void dump_interface(const interface_t *interface);

#endif
