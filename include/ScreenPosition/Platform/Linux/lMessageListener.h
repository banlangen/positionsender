#ifndef _LMESSAGE_LISTENER_H
#define _LMESSAGE_LISTENER_H
#include "messageListener.h"
#include "msgInfo.h"

class lMessageListener : public MessageListener {
public:
   bool connect();
   bool getConnectionStatus();
   bool sendMessage(MessageInfo &);
};
#endif
