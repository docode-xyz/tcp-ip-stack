#include "../src/common.h"

extern graph_t *topology_build();

int main(void) {
  graph_t *topology = topology_build();
  if (!topology) fprintf(stderr, "[ERROR]: main: Failed to create topology!\n");

  dump_graph(topology);

  fprintf(stdout, "All Done!\n");
  return 0;
}