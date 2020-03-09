#include "messageProvider.h"
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <stdio.h>
#include <memory>
#include <pthread.h>
#include <string.h>
#include "qMsgInfo.h"
#include "q_semaphore.h"
#include "q_queue.h"

#define ATTACH_POINT_TOUCH "avm_touch_position"

std::shared_ptr<name_attach_t> MessageProvider::attach = std::shared_ptr<name_attach_t>(name_attach(NULL, ATTACH_POINT_TOUCH, 0));

static q_semaphore_t g_message_sem;
static q_queue_t g_message_queue;

MessageProvider::MessageProvider() {
    q_sem_init(&g_message_sem, 0);
    q_queue_init(&g_message_queue);
}

MessageProvider::~MessageProvider() {
    q_sem_destroy(&g_message_sem);
    q_queue_deinit(&g_message_queue);
}


bool MessageProvider::prepare() {
    //create channel
    //attach = std::shared_ptr<name_attach_t>(name_attach(NULL, ATTACH_POINT_TOUCH, 0));
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

bool MessageProvider::getMessage(MessageInfo *m_info) {
    MessageInfo *tmp = NULL;
    tmp = (MessageInfo *)q_queue_deq(&g_message_queue);
    if (tmp == NULL) {
        return false;
    } else {
        m_info = tmp;
        return true;
    }
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
            MessageInfo *m_info = new MessageInfo();
            memset(m_info, 0, sizeof(MessageInfo));
            m_info->screen_event = rmsg.msg_content.screen_event;
            m_info->touch_id = rmsg.msg_content.touch_id;
            m_info->x = rmsg.msg_content.x;
            m_info->y = rmsg.msg_content.y;            
            q_queue_enq(&g_message_queue, m_info);
        } else if (0 == rcvid) {
            printf("pulse msg received!\n");
        } else { // == -1
            printf("Failed to receive message with error: %s\n", strerror(errno));
            break;
        }
    }
}
