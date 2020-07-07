#include "common.h"

void glist_init(glist_t *curr) {
  curr->left = NULL;
  curr->right = NULL;
}

void glist_push_right(glist_t *curr, glist_t *new_entry) {
  if (!curr->right) {
    curr->right = new_entry;
    new_entry->left = curr;
    return;
  }

  glist_t *temp = curr->right;
  curr->right = new_entry;
  new_entry->left = curr;
  new_entry->right = temp;
  temp->left = new_entry;
}

void glist_push_left(glist_t *curr, glist_t *new_entry) {
  if (!curr->left) {
    new_entry->left = NULL;
    new_entry->right = curr;
    curr->left = new_entry;
  }

  glist_t *temp = curr->left;
  temp->right = new_entry;
  new_entry->left = temp;
  new_entry->right = curr;
  curr->left = new_entry;
}

void glist_remove(glist_t *curr) {
  if (!curr->left) {
    if (curr->right) {
      curr->right->left = NULL;
      curr->right = NULL;
      return;
    }
    return;
  }
  if (!curr->right) {
    curr->left->right = NULL;
    curr->left = NULL;
    return;
  }

  curr->left->right = curr->right;
  curr->right->left = curr->left;
  curr->left = NULL;
  curr->right = NULL;
}

// clang-format off
void glist_remove_list(glist_t *curr) {
  glist_t *glist_ptr = NULL;

  ITERATE_GLIST_BEGIN(curr, glist_ptr) { 
      glist_remove(glist_ptr); 
  } ITERATE_GLIST_END(curr, glist_ptr);
}
// clang-format on

uint32_t glist_list_count(glist_t *curr) {
  uint32_t count = 0;
  glist_t *glist_ptr = NULL;

  // clang-format off
  ITERATE_GLIST_BEGIN(curr, glist_ptr) { 
      count++; 
  } ITERATE_GLIST_END(curr, glist_ptr);
  // clang-format on
  return count;
}

// clang-format off
void glist_priority_insert(glist_t *curr,
                           glist_t *new_entry,
                           int8_t (*comp_fn)(void *, void *),
                           size_t offset) {
  // clang-format on

  glist_t *_curr = NULL, *_prev = NULL;

  glist_init(new_entry);

  if (IS_GLIST_LIST_EMPTY(curr)) {
    glist_push_right(curr, new_entry);
    return;
  }

  /* Only one node*/
  if (curr->right && !curr->right->right) {
    if (comp_fn(GLIST_GET_USER_DATA_FROM_OFFSET(curr->right, offset),
                GLIST_GET_USER_DATA_FROM_OFFSET(new_entry, offset)) == -1) {
      glist_push_right(curr->right, new_entry);
    } else {
      glist_push_right(curr, new_entry);
    }
    return;
  }

  if (comp_fn(GLIST_GET_USER_DATA_FROM_OFFSET(new_entry, offset),
              GLIST_GET_USER_DATA_FROM_OFFSET(curr->right, offset)) == -1) {
    glist_push_right(curr, new_entry);
    return;
  }

  ITERATE_GLIST_BEGIN(curr, _curr) {
    if (comp_fn(GLIST_GET_USER_DATA_FROM_OFFSET(new_entry, offset),
                GLIST_GET_USER_DATA_FROM_OFFSET(_curr, offset)) != -1) {
      _prev = _curr;
      continue;
    }

    glist_push_right(_curr, new_entry);
    return;
  }
  ITERATE_GLIST_END(curr, _curr);

  /*Add in the end*/
  glist_push_right(_prev, new_entry);
}
