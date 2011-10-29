#include "listener.h"          
#include "request.h"

void Beanpole::PushRouteListener::onRequest(Beanpole::Request* request)
{          
	this->_callback((Beanpole::PushRequest*)request);
}