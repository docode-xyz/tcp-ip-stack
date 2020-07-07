#include "common.h"

/**
 * @brief Build the topology
 */
graph_t *topology_build() {
  graph_t *topology = graph_create_new("FIRST TOPOLOGY");
  if (!topology) goto err_topology;

  /* Create a nodes */
  node_t *R0 = graph_create_node(topology, "R0");
  if (!R0) goto err_node;
  node_t *R1 = graph_create_node(topology, "R1");
  if (!R1) goto err_node;
  node_t *R2 = graph_create_node(topology, "R2");
  if (!R2) goto err_node;

  /* Connecting */
  graph_insert_link_btw_2_nodes(R0, R1, "eth0/0", "eth0/1", 1);
  graph_insert_link_btw_2_nodes(R1, R2, "eth0/2", "eth0/3", 1);
  graph_insert_link_btw_2_nodes(R0, R2, "eth0/4", "eth0/5", 1);

  return topology;

err_topology:
  fprintf(stderr, "[ERROR]: Failed to create a new topology!\n");
  return NULL;

err_node:
  return NULL;
}