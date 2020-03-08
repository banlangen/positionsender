#include "messageProvider.h"
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "qMsgInfo.h"

#define ATTACH_POINT_TOUCH "avm_touch_position"

name_attach_t *MessageProvider::attach = name_attach(NULL, ATTACH_POINT_TOUCH, 0);

bool MessageProvider::prepare() {
    //create channel
    //attach = name_attach(NULL, ATTACH_POINT_TOUCH, 0);
    if (NULL == attach) {
        printf("name_attach error!\n");
        return false;
    }
    //create a thread
    pthread_t tid;
    if (EOK != pthread_create(&tid, NULL, msg_rcv_thread_loop, NULL)) {
        printf("unable to create msg receiver thread - %s\n", strerror(errno));
    }
    return true;
}

bool MessageProvider::getMessage(MessageInfo &m_info) {
    return true;
}

void *MessageProvider::msg_rcv_thread_loop(void *arg) {
    while(true) {
        printf("start screen position MsgReceive..\n");
        QMessageInfo rmsg;
        int rcvid = MsgReceive(attach->chid, &rmsg, sizeof(QMessageInfo), NULL);
        if (rcvid > 0) {
            /*name_open() sends a connect message, must respond with EOK*/
            if (rmsg.msg_header.type == _IO_CONNECT) {
                printf("connect received!\n");
                MsgReply(rcvid, EOK, NULL, 0);
                continue;
            }
            /* Some oth QNX IO message was received, reject it */
            if (rmsg.msg_header.type > _IO_BASE && rmsg.msg_header.type <= _IO_MAX) {
                MsgError(rcvid, ENOSYS);
                continue;
            }
            /* handle received message */
            
        } else if (0 == rcvid) {
            printf("pulse msg received!\n");
        } else { // == -1
            printf("Failed to receive message with error: %s\n", strerror(errno));
            break;
        }
    }
}
