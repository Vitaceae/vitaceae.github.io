/**
 * Copyright (C) 2018 Dexatek Technology Ltd.
 *
 * singly_linked_list.c
 *
 * This is proprietary information of Dexatek Technology Ltd. All Rights
 * Reserved. Reproduction of this documentation or the accompanying programs in
 * any manner whatsoever without the written permission of Dexatek Technology
 * Ltd. is strictly forbidden.
 */

#include "singly_linked_list.h"

#ifndef NULL
#define NULL            0
#endif

/** CAS: compare and exchange; to assure atomic operation
 *      for processor not supporting cas instructions; unsuitable for SMP
 *      check if there is compiler-specific implementation
 */
slist_node_t *_cas(slist_node_t **ptr, slist_node_t *old, slist_node_t *new_node)
{
    slist_node_t *prev;

    //ATOMIC();
    prev = (slist_node_t *)*(volatile slist_node_t **)ptr;
    if (prev == old) {
        *(slist_node_t **)ptr = new_node;
    }
    //END_ATOMIC();

    return prev;
}
#define __cas(ptr, _old, _new)          _cas(ptr, _old, _new)


int slist_add(slist_node_t *new_node, slist_head_t *head)
{
    slist_node_t *first;

    do {
        //use volatile to prevent from compiler opptimization:
        //  first = head->first
        //  while(){ ... }
        //there may be inconsistency if head->first is modified by other threads
        new_node->next = first = (slist_node_t *)
                                 *(volatile slist_node_t **)&head->first;
    } while (__cas(&head->first, first, new_node) != first);

    return !first;
}


/**
 * remove a certain node
 */
void slist_remove(slist_head_t *h, slist_node_t *target)
{
    //address of the 'next' pointer
    slist_node_t **next = &h->first;

    //walk the list, modify the value of list->next directly
    while (*next != target) {
        next = &(*next)->next;
    }

    *next = target->next;
}


/**
 * reverse the list if you want to traverse in the order of registration
 */
slist_node_t *slist_reverse(slist_node_t *head)
{
    slist_node_t *new_head = NULL;

    while (head) {
        slist_node_t *tmp = head;
        head = head->next;
        tmp->next = new_head;
        new_head = tmp;
    }

    return new_head;
}

/**
 * reverse the list if you want to traverse in the order of registration
 */
slist_node_t *slist_reverse_except_head(slist_node_t *head)
{
    slist_node_t *new_head = NULL;
    slist_node_t *h = head;
    slist_node_t *tail = head->next;

    if (tail == NULL) {
        return head;
    }

    while (head) {
        slist_node_t *tmp = head;
        head = head->next;
        tmp->next = new_head;
        new_head = tmp;
    }

    tail->next = NULL;
    h->next = new_head;

    return h;
}
