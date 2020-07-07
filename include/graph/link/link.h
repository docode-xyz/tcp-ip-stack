/**
 * @file link.h
 * @author Valery Ivanov
 * @date 7 Jul 2020
 * @brief Link representation
 */
#ifndef LINK_H
#define LINK_H

#include "../node/interface/interface.h"

typedef struct link {
  interface_t if_from;
  interface_t if_to;
  uint32_t cost;
} link_t;


/**
 * @brief Create a new link
 * 
 * @return New link or NULL on failure
 */
link_t *link_create_new(const char *if_from, const char *if_to,
                        const uint32_t cost);

#endif