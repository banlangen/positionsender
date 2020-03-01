#ifndef _MESSAGE_LISTENER_H
#define _MESSAGE_LISTENER_H
class MessageListener {
public:
    virtual void attach();
    virtual bool sendMessage();
    bool getAttachStatus();
protected:
    bool isAttached = false;
};
#endif
