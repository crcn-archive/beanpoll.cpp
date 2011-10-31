#include "listener.h"          
#include "request.h"
              
namespace Beanpole
{
	void PushRouteListener::onRequest(Beanpole::Request* request)
	{          
		this->_callback((PushRequest*)request);
	}
};

namespace Beanpole
{
	void PullRouteListener::onRequest(Beanpole::Request* request)
	{          
		this->_callback((PullRequest*)request);
	}
}
