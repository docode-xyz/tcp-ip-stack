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