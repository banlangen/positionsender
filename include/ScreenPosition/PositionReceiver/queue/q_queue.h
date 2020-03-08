#ifndef __WM_QUEUE_H__
#define __WM_QUEUE_H__
// System dependencies
#include <pthread.h>
#include <string.h>

// Camera dependencies
#include "q_list.h"

typedef struct {
    struct q_list list;
    void *data;
} q_node_t;

typedef struct {
    q_node_t head; /* dummy head */
    uint32_t size;
    pthread_mutex_t lock;
} q_queue_t;

static inline int32_t q_queue_init(q_queue_t *queue)
{
    pthread_mutex_init(&queue->lock, NULL);
    q_list_init(&queue->head.list);
    queue->size = 0;
    return 0;
}

static inline int32_t q_queue_enq(q_queue_t *queue, void *data)
{
	q_node_t *node =
        (q_node_t *)malloc(sizeof(q_node_t));
    if (NULL == node) {
        return -1;
    }

    memset(node, 0, sizeof(q_node_t));
    node->data = data;

    pthread_mutex_lock(&queue->lock);
    q_list_add_tail_node(&node->list, &queue->head.list);
    queue->size++;
    pthread_mutex_unlock(&queue->lock);

    return 0;
}

static inline void *q_queue_deq(q_queue_t *queue)
{
	q_node_t *node = NULL;
    void *data = NULL;
    struct q_list *head = NULL;
    struct q_list *pos = NULL;

    pthread_mutex_lock(&queue->lock);
    head = &queue->head.list;
    pos = head->next;
    if (pos != head) {
        node = member_of(pos, q_node_t, list);
        q_list_del_node(&node->list);
        queue->size--;
    }
    pthread_mutex_unlock(&queue->lock);

    if (NULL != node) {
        data = node->data;
        free(node);
    }

    return data;
}

static inline int32_t q_queue_flush(q_queue_t *queue)
{
	q_node_t *node = NULL;
    struct q_list *head = NULL;
    struct q_list *pos = NULL;

    pthread_mutex_lock(&queue->lock);
    head = &queue->head.list;
    pos = head->next;

    while(pos != head) {
        node = member_of(pos, q_node_t, list);
        pos = pos->next;
        q_list_del_node(&node->list);
        queue->size--;

        /* TODO later to consider ptr inside data */
        /* for now we only assume there is no ptr inside data
         * so we free data directly */
        // if (NULL != node->data) {
        //     free(node->data);
        // }
        free(node);

    }
    queue->size = 0;
    pthread_mutex_unlock(&queue->lock);
    return 0;
}

static inline int32_t q_queue_remove(q_queue_t *queue,void* data)
{
    if(data == NULL) return -1;
	q_node_t *node = NULL;
    struct q_list *head = NULL;
    struct q_list *pos = NULL;

    pthread_mutex_lock(&queue->lock);
    head = &queue->head.list;
    pos = head->next;

    while(pos != head) {
        node = member_of(pos, q_node_t, list);
        pos = pos->next;
        if(node->data == data) {
            q_list_del_node(&node->list);
            queue->size--;
            free(node);
            break;
        } 
    }
    pthread_mutex_unlock(&queue->lock);
    return 0;
}

static inline int32_t q_queue_deinit(q_queue_t *queue)
{
	q_queue_flush(queue);
    pthread_mutex_destroy(&queue->lock);
    return 0;
}

#endif
