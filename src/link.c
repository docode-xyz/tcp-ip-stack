#include "common.h"

link_t *link_create_new(const char *from_if_name, const char *to_if_name,
                        const uint32_t cost) {
  link_t *new_link = calloc(1, sizeof(link_t));
  if (!new_link) {
    fprintf(stderr, "%s", "[ERROR]: Failed to create a new link!\n");
    return NULL;
  }

  strncpy(new_link->if_from.if_name, from_if_name, INTERFACE_NAME_LEN);
  new_link->if_from.if_name[INTERFACE_NAME_LEN - 1] = '\0';
  strncpy(new_link->if_to.if_name, to_if_name, INTERFACE_NAME_LEN);
  new_link->if_to.if_name[INTERFACE_NAME_LEN - 1] = '\0';

  new_link->cost = cost;

  return new_link;
}