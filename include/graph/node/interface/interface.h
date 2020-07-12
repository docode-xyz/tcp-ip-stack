/**
 * @file interface.h
 * @author Valery Ivanov
 * @date 7 Jul 2020
 * @brief Interface representation
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "../../link/link.h"
#include "../node.h"

#define INTERFACE_NAME_LEN 16

/* Forward declaration */
typedef struct link link_t;

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
  net_iface_prop_t net_iface_prop;
} interface_t;

void interface_set_mac_addr(interface_t *iface);

void dump_interface(const interface_t *interface);

#endif