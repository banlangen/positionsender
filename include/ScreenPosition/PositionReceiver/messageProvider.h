#include "msgInfo.h"
#include <memory>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

class MessageProvider {
public:
    MessageProvider();
    ~MessageProvider();
    bool prepare(); 
    bool getMessage(MessageInfo *);
private:
    static void *msg_rcv_thread_loop(void *arg);
    //static name_attach_t *attach;
    static std::shared_ptr<name_attach_t> attach;
};
