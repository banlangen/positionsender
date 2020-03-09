#ifndef _MESSAGE_LISTENER_H
#define _MESSAGE_LISTENER_H
#include "msgInfo.h"

class MessageListener {
public:
    virtual bool connect();
    virtual bool sendMessage(MessageInfo &);
    virtual bool getConnectionStatus() = 0;
protected:
    bool m_isConnected = false;
};
#endif
