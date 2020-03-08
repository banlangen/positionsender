#ifndef _CAM_COND_H
#define _CAM_COND_H

#define PTHREAD_COND_INIT(cond) \
  ({                                   \
    int rc = 0;                       \
    pthread_condattr_t cond_attr;     \
    rc = pthread_condattr_init(&cond_attr);   \
    if (rc == 0) {                            \
      rc = pthread_condattr_setclock(&cond_attr, CLOCK_MONOTONIC);  \
      if (rc == 0) {                                 \
        rc = pthread_cond_init(cond, &cond_attr);  \
      } \
    } \
    rc; \
  })

#endif // CAM_COND_H
