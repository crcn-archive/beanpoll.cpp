#include "listener.hpp"          
#include "request.hpp"
              
namespace Beanpoll
{
	void PushRouteListener::onRequest(Beanpoll::Request* request)
	{          
		this->_callback((PushRequest*)request);
	}
};

namespace Beanpoll
{
	void PullRouteListener::onRequest(Beanpoll::Request* request)
	{          
		this->_callback((PullRequest*)request);
	}
}
