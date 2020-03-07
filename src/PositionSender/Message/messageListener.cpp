#include "messageListener.h"
#include <iostream>

bool MessageListener::connect() {
    std::cout << "MessageListener::attach()" << std::endl;
    return true;
}

bool MessageListener::sendMessage(MessageInfo &m_info) {
    std::cout << "MessageListener::sendMessage()" << std::endl;
    return true;
}

bool MessageListener::getConnectionStatus() {
    std::cout << "MessageListener::getAttachStatus" << std::endl;
    return true;
}
