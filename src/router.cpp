        

#include "router.h"  
#include "listener.h"
#include <iostream>        


void Beanpole::ConcreteDispatcher::dispatch(Beanpole::Data* data)
{
	std::vector<Beanpole::RouteListener*>* listeners = this->_collection.getRouteListeners(data->channel);    
	
	Beanpole::ConcreteDispatcher::dispatch(data, listeners);
}


void Beanpole::Router::on(const char* route, void (*callback)(Beanpole::PullRequest*))
{                
	std::cout << "PULL" << std::endl;
}

void Beanpole::Router::on(const char* route, void (*callback)(Beanpole::PushRequest*))
{
	std::cout << "PUSH" << std::endl;
};