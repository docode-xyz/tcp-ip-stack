/**
 * @file glist.h
 * @author Valery Ivanov
 * @date 5 Jul 2020
 * @brief Self-pointed doubly-linker list
 */

#ifndef GLIST_H
#define GLIST_H

#include <stddef.h>
#include <stdint.h>

#include "../../include/graph/graph.h"

/**
 * @brief Self-pointed doubly-linker list a.k.a Glue List
 */
typedef struct glist {
  struct glist *left;
  struct glist *right;

} glist_t;

#define BASE(glist_ptr) ((glist_ptr)->right)

#define ITERATE_GLIST_BEGIN(glist_ptr_start, glist_ptr) \
  {                                                     \
    glist_t *_glist_ptr = NULL;                         \
    glist_ptr = BASE(glist_ptr_start);                  \
    for (; glist_ptr != NULL; glist_ptr = _glist_ptr) { \
      _glist_ptr = (glist_ptr)->right;

// clang-format off
#define ITERATE_GLIST_END(glist_ptr_start, glist_ptr) \
  }}
// clang-format on

#define GLIST_GET_USER_DATA_FROM_OFFSET(glist_ptr, offset) \
  (void *)((char *)(glist_ptr)-offset)

extern void glist_init(glist_t *curr);

extern void glist_push_right(glist_t *curr, glist_t *new_entry);

extern void glist_push_left(glist_t *curr, glist_t *new_entry);

extern void glist_remove(glist_t *curr);

extern void glist_remove_list(glist_t *curr);

// clang-format off
#define GLIST_TO_STRUCT(fn_name, structure_name, field_name)                                            \
    static inline structure_name * fn_name(glist_t *glist_ptr){                                         \
        return (structure_name *)((char *)(glist_ptr) - (char *)&(((structure_name *)0)->field_name));  \
    }
// clang-format on

#define IS_GLIST_LIST_EMPTY(glist_ptr) \
  ((glist_ptr)->right == NULL && (glist_ptr)->left == NULL)

extern uint32_t glist_list_count(glist_t *curr);

// clang-format off
extern void glist_priority_insert(glist_t *curr,
                                  glist_t *new_entry,
                                  int8_t (*comp_fn)(void *, void *),
                                  size_t offset);
// clang-format on

#endif
