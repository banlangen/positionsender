#include <stdio.h>
#include "messageManager.h"

void MessageManager::createMessage(int s_event, int touch_id, float x, float y) {
    m_info = {s_event, touch_id, x, y};
}

MessageInfo& MessageManager::getMessage() {
    return m_info;
}

void MessageManager::requestListener(std::shared_ptr<MessageListener> &mListener) {
    m_listener = mListener;
}

bool MessageManager::sendMessage() {
    if (!m_listener->getConnectionStatus()) {
        //m_listener->connect();
        printf("please establish the connection beforehand\n");
        return false;
    }
    return m_listener->sendMessage(m_info);
}


