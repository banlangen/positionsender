#ifndef _Q_MESSAGE_LISTENER
#define _Q_MESSAGE_LISTENER
#include "messageListener.h"

class qMessageListener : public MessageListener {
public:
    void attach();
    bool sendMessage();
};
#endif
