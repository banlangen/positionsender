#ifndef _Q_MESSAGE_LISTENER
#define _Q_MESSAGE_LISTENER
#include "messageListener.h"
#include "qMsgInfo.h"

class qMessageListener : public MessageListener {
public:
    int m_tpChID = 0;
    bool connect();
    bool sendMessage(MessageInfo &);
    bool getConnectionStatus();
};
#endif
