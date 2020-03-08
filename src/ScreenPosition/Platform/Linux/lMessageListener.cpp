#include "lMessageListener.h"
#include <stdio.h>

bool lMessageListener::connect() {
    printf("lMessageListener::connect\n");
    m_isConnected = true;
    return true;
}

bool lMessageListener::getConnectionStatus() {
    return m_isConnected;
}

bool lMessageListener::sendMessage(MessageInfo &m_info) {
    printf("lMessageInfo.screen_event: %d\n", m_info.screen_event);
    printf("lMessageInfo.touch_id: %d\n", m_info.touch_id);
    printf("lMessageInfo.x: %f\n", m_info.x);
    printf("lMessageInfo.x: %f\n", m_info.y);
    return true;
}

