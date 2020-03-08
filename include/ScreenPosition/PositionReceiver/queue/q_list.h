#ifndef __Q_LIST_H
#define __Q_LIST_H

#include <stddef.h>
// System dependency
#include <stdlib.h>

#define member_of(ptr, type, member) ({ \
  const decltype(((type *)0)->member) *__mptr = (ptr); \
  (type *)((char *)__mptr - offsetof(type,member));})

struct q_list {
  struct q_list *next, *prev;
};

static inline void q_list_init(struct q_list *ptr)
{
  ptr->next = ptr;
  ptr->prev = ptr;
}

static inline void q_list_add_tail_node(struct q_list *item,
  struct q_list *head)
{
  struct q_list *prev = head->prev;

  head->prev = item;
  item->next = head;
  item->prev = prev;
  prev->next = item;
}

static inline void q_list_insert_before_node(struct q_list *item,
  struct q_list *node)
{
  item->next = node;
  item->prev = node->prev;
  item->prev->next = item;
  node->prev = item;
}

static inline void q_list_del_node(struct q_list *ptr)
{
  struct q_list *prev = ptr->prev;
  struct q_list *next = ptr->next;

  next->prev = ptr->prev;
  prev->next = ptr->next;
  ptr->next = ptr;
  ptr->prev = ptr;
}

#endif
