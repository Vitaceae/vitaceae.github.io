/**
 * Copyright (C) 2018 Dexatek Technology Ltd.
 *
 * singly_linked_list.h
 *
 * This is proprietary information of Dexatek Technology Ltd. All Rights
 * Reserved. Reproduction of this documentation or the accompanying programs in
 * any manner whatsoever without the written permission of Dexatek Technology
 * Ltd. is strictly forbidden.
 */

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "sys_util.h"

#ifndef NULL
#define NULL                            0
#endif


typedef struct slist_head {
    struct slist_node *first;
} slist_head_t;

typedef struct slist_node {
    struct slist_node *next;
} slist_node_t;

#define SLIST_HEAD_INIT(name)         { NULL }
#define SLIST_HEAD(name)              struct slist_head name = \
                                                SLIST_HEAD_INIT(name)

static inline void init_slist_head(struct slist_head *list)
{
    list->first = NULL;
}

/**
 *  ptr:    a loop cursor of a user-defined struct pointer
 *          the struct mentioned above should contain 'struct slist_node'
 *  type:   the type of the user-defined struct
 *  member: the name of 'struct slist_node' in the user-defined struct
 */
#define slist_entry(ptr, type, member) \
            container_of(ptr, type, member)

/**
 *  ptr:    a loop cursor of type 'slist_node *'
 *  node:   a node of type 'slist_node *' in the list
 */
#define slist_for_each(ptr, node) \
            for ((ptr) = (node); ptr; (ptr) = (ptr)->next)

/**
 *  ptr:    a loop cursor of a user-defined struct pointer
 *          the struct mentioned above should contain 'struct slist_node'
 *  node:   the fist entry of the list; the type should be 'struct slist_node *'
 *  type:   the type of the user-defined struct
 *  member: the name of 'struct slist_node' in the user-defined struct
 */
#define slist_for_each_entry(ptr, node, type, member) \
            for ((ptr) = slist_entry(node, type, member);               \
                 (node !=NULL) && ((uintptr_t)(ptr) + offsetof(type, member)) != 0;      \
                 (ptr) = slist_entry((ptr)->member.next, type, member))


int slist_add(struct slist_node *new_node, struct slist_head *head);
int slist_delete(struct slist_node *new_node, struct slist_head *head);
slist_node_t *slist_reverse(struct slist_node *head);
slist_node_t *slist_reverse_except_head(slist_node_t *head);

#endif //SINGLY_LINKED_LIST_H
