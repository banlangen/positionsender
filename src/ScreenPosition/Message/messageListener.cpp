#include "messageListener.h"
#include <iostream>

bool MessageListener::connect() {
    std::cout << "MessageListener::connect()" << std::endl;
    return true;
}

bool MessageListener::sendMessage(MessageInfo &m_info) {
    std::cout << "MessageListener::sendMessage()" << std::endl;
    return true;
}

/*bool MessageListener::getConnectionStatus() {
    std::cout << "MessageListener::getConnectionStatus" << std::endl;
    return true;
}*/
