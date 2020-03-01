#include "messageListener.h"
#include <iostream>

void MessageListener::attach() {
    std::cout << "MessageListener::attach()" << std::endl;
}

bool MessageListener::sendMessage() {
    std::cout << "MessageListener::sendMessage()" << std::endl;
    return true;
}

bool MessageListener::getAttachStatus() {
    std::cout << "MessageListener::getAttachStatus" << std::endl;
    return true;
}
