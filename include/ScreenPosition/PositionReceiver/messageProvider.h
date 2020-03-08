#include "msgInfo.h"

class MessageProvider {
public:
   bool prepare(); 
   bool getMessage(MessageInfo &m_info);
};
