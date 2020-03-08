#ifndef _Q_MSG_INFO_H
#define _Q_MSG_INFO_H
#include <sys/neutrino.h>
#include "msgInfo.h"

typedef struct QMessageInfo {
    struct _pulse msg_header;
    MessageInfo msg_content;
} QMessageInfo;
#endif
