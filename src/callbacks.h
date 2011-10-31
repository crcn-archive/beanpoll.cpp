#ifndef CALLBACKS_H_
#define CALLBACKS_H_     

// #include "request.h"                
namespace Beanpole
{
	class PushRequest;
	class PullRequest;  
	class RequestStream;
};
                                             
      
typedef void (PushCallback)(Beanpole::PushRequest*);  
typedef void (PullCallback)(Beanpole::PullRequest*);
typedef void (StreamCallback)(Beanpole::RequestStream*);

#endif