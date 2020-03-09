#include "qMessageListener.h"
#include "msgInfo.h"
#include "qMsgInfo.h"
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <stdio.h>

#define ATTACH_POINT_TOUCH "avm_touch_position"

bool qMessageListener::sendMessage(MessageInfo &m_info) {
    //MessageManager::getInstance();
    QMessageInfo smsg;
    smsg.msg_content.screen_event = m_info.screen_event;
    smsg.msg_content.touch_id = m_info.touch_id;
    smsg.msg_content.x = m_info.x;
    smsg.msg_content.y = m_info.y;
    int tryCount = 0;
    while (tryCount < 3) {
        int ret = MsgSend(m_tpChID, &smsg, sizeof(QMessageInfo), NULL, 0); 
        if (ret == -1) {
            printf("Error during MsgSend\n");
            tryCount++;
        } else {
            printf("Message Send\n");
            break;
        }
    }
    if (3 == tryCount) {
        printf("Message Sent failed\n");
        return false;
    } else {
        return true;
    } 
}

bool qMessageListener::getConnectionStatus() {
    printf("qMessageListener::getConnectionStatus()\n");
    return m_isConnected;
}

bool qMessageListener::connect() {
    m_tpChID = name_open(ATTACH_POINT_TOUCH, 0);
    int cycleCount = 0;
    while(true) {
        if (m_tpChID == -1) {
            printf("failed to establish connection, try again...\n");
            cycleCount++;
            usleep(300 * 1000);
        } else {
            printf("connection is establised successfully, m_tpChID is %d\n", m_tpChID); 
            m_isConnected = true;
            break;
        }
        if (cycleCount > 10) break;
    }
    return ((cycleCount < 10) ? true : false);
}
