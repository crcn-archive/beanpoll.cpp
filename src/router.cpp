        
                    
#include "request.h"
#include "router.h"  
#include "listener.h"     
#include "utils.h"
#include <iostream>                
#include <vector>   
#include <pthread.h>   


void Beanpole::ConcreteDispatcher::dispatch(Beanpole::Data* data)
{
	std::vector<Beanpole::RouteListener*>* listeners = this->_collection.getRouteListeners(data->channel);    
	
	Beanpole::ConcreteDispatcher::dispatch(data, listeners);
}                                 

        
void* dispatch_threaded_request(void* request)
{                                                      
	((Beanpole::Request*)request)->next(); 
	delete (Beanpole::Request*)request;                        
	return NULL;
}


void Beanpole::ConcreteDispatcher::dispatch(Beanpole::Data* data, std::vector<RouteListener*>* listeners)
{                           
	pthread_t thread;
	
	for(int i = listeners->size(); i--;)
	{                                                          
		pthread_create(&thread, NULL, &dispatch_threaded_request, (void*)(this->request(data, (*listeners)[i])));
		// Beanpole::Request* request = this->request(data, (*listeners)[i]);
		
		// request->next();
		
		// delete request;
	}
}        

Beanpole::Request* Beanpole::ConcreteDispatcher::request(Beanpole::Data* data, Beanpole::RouteListener* listener)
{                                     
	return new Beanpole::Request(data, listener, this);
}

void Beanpole::ConcreteDispatcher::addRouteListener(RouteListener* listener)
{                    
	this->_collection.addRouteListener(listener);
}          

Beanpole::Data* Beanpole::Router::request(const char* channel)
{          
	return new Beanpole::Data(Beanpole::Parser::parseChannel(channel), this);
}


void Beanpole::Router::on(std::string route, PullCallback* callback)
{                
	std::cout << "PULL" << std::endl;
}

void Beanpole::Router::on(std::string route, PushCallback* callback)
{                                                                   
	std::vector<RouteExpression*> expressions;

	Beanpole::Parser::parseRoute(route, expressions);


	for(int i = expressions.size(); i--;)
	{                                       
		this->_pusher->addRouteListener(new Beanpole::PushRouteListener(expressions[i], callback));
	}                                 

};     

void Beanpole::Router::push(Data* data)
{
	this->_pusher->dispatch(data);  
}   

void Beanpole::Router::pull(Data* data)
{
	this->_puller->dispatch(data);
}