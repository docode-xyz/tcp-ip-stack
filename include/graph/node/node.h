/**
 * @file node.h
 * @author Valery Ivanov
 * @date 7 Jul 2020
 * @brief Node representation
 */
#ifndef NODE_H
#define NODE_H

#include "../../../lib/glist/glist.h"
#include "interface/interface.h"

#define NODE_NAME_LEN 16
#define MAX_IF_PER_NODE 10

/* Forward declaration */
typedef struct interface interface_t;

typedef struct node {
  char node_name[NODE_NAME_LEN];
  interface_t *if_arr[MAX_IF_PER_NODE]; /**< Empty slots on the routing devices;
                                     if NULL it's means that slot is empty  */
  glist_t graph_node;
} node_t;

/**
 * @brief Create a new node
 *
 * @return New node or NULL on failure
 */
node_t *node_create_new(const char *name);

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

void dump_node(const node_t *node);

#endif