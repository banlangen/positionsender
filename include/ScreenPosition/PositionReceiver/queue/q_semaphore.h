#ifndef __Q_SEMAPHORE_H__
#define __Q_SEMAPHORE_H__

// System dependencies
#include <pthread.h>
#include <errno.h>
#include "q_cond.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    int val;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} q_semaphore_t;

static inline void q_sem_init(q_semaphore_t *s, int n)
{
    pthread_mutex_init(&(s->mutex), NULL);
    PTHREAD_COND_INIT(&(s->cond));
    s->val = n;
}

static inline void q_sem_post(q_semaphore_t *s)
{
    pthread_mutex_lock(&(s->mutex));
    s->val++;
    pthread_cond_signal(&(s->cond));
    pthread_mutex_unlock(&(s->mutex));
}

static inline int q_sem_wait(q_semaphore_t *s)
{
    int rc = 0;
    pthread_mutex_lock(&(s->mutex));
    while (s->val == 0)
        rc = pthread_cond_wait(&(s->cond), &(s->mutex));
    s->val--;
    pthread_mutex_unlock(&(s->mutex));
    return rc;
}

static inline int q_sem_timedwait(q_semaphore_t *s, const struct timespec *abs_timeout)
{
    int rc = 0;
    pthread_mutex_lock(&(s->mutex));
    while (s->val == 0 && rc != ETIMEDOUT)
        rc = pthread_cond_timedwait(&(s->cond), &(s->mutex), abs_timeout);

    if (s->val > 0)
        s->val--;

    pthread_mutex_unlock(&(s->mutex));

    /* sem_timedwait returns -1 for failure case, and failure code is in errno
     */
    if (rc != 0) {
        errno = rc;
        rc = -1;
    }
    return rc;
}

static inline void q_sem_destroy(q_semaphore_t *s)
{
    pthread_mutex_destroy(&(s->mutex));
    pthread_cond_destroy(&(s->cond));
    s->val = 0;
}

#ifdef __cplusplus
}
#endif

#endif
