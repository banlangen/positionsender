#ifndef _MESSAGE_MANAGER_H
#define _MESSAGE_MANAGER_H
#include <memory>
#include "messageListener.h"
#include "msgInfo.h"

class MessageManager {
public:    
    static MessageManager& getInstance() {
        static MessageManager instance;
        return instance;
    }
    ~MessageManager() {};
    void createMessage(int/*screen_event*/, int/*touch_id*/, float/*x position*/, float/*y position*/);
    MessageInfo& getMessage();
    bool sendMessage(); 
    void requestListener(std::shared_ptr<MessageListener> &mListener);
    
    //MessageManager(MessageManager const &) = delete;
    //void operator=(MessageManager const &) = delete;

private:
    MessageManager() { };
    //MessageManager(MessageManager const &);
    //void operator=(MessageManager const &); 
    std::shared_ptr<MessageListener> m_listener;
    MessageInfo m_info;
};
#endif
