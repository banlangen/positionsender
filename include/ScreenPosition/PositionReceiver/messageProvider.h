#include "msgInfo.h"
#include <sys/iofunc.h>
#include <sys/dispatch.h>

class MessageProvider {
public:
   bool prepare(); 
   bool getMessage(MessageInfo &m_info);
private:
   static void *msg_rcv_thread_loop(void *arg);
   static name_attach_t *attach;
};
