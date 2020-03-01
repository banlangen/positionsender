#include "messageManager.h"

void MessageManager::createMessage(int s_event, int touch_id, float x, float y) {
    m_info = {s_event, touch_id, x, y};
}

MsgInfo& MessageManager::getMessage() {
    return m_info;
}

void MessageManager::requestListener(std::shared_ptr<MessageListener> &mListener) {
    m_listener = mListener;
}

bool MessageManager::sendMessage() {
    if (!m_listener->getAttachStatus()) {
        m_listener->attach();
    }
    return m_listener->sendMessage();
}


