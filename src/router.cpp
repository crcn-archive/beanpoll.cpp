

#include "request.hpp"
#include "router.hpp"  
#include "listener.hpp"  
#include "middleware.hpp"   
#include "utils.hpp"
#include <iostream>                
#include <vector>   
#include <pthread.h>     


namespace Beanpoll
{
	/*void* dispatch_threaded_request(void* request)
	{                                                      
		((Request*) request)->next(); 
		delete (Request*) request;                        
		return NULL;
	}*/                    
	
	
	void ConcreteDispatcher::dispatch(Message* message, std::vector<RouteListener*>* listeners)
	{                         
		
		for(int i = listeners->size(); i--;)
		{               
			//void* val;
			continue;
			
			//TODO: check if request is threaded.
			RouteListener* listener = (*listeners)[i];
			Message* clonedMessage = message->clone();
			
			RequestMiddleware* middleware = RequestMiddleware::expand(clonedMessage->channel, listener, this);          
			
			Request* request = this->request(clonedMessage, middleware);            
			
			
			request->onComplete(cleanupRequest);
			request->next();
			
			
			//async call per listener. Typically one except push requests
			//this->_threadBoss.createTask((void*)request, &dispatch_threaded_request);
		}                      
		
		//done with the data - requests handle it from here.
		delete message;
	}
	
	char ConcreteDispatcher::cleanupRequest(Request* request)
	{
		delete request;
		return 0;
	}
	
	
	void* init_thread_request(void* msg)
	{
		//Message* message = ((Message*)msg);
		//std::vector<RouteListener*>* listeners = message->dispatcher->_collection.getRouteListeners(message->channel);    
		
		//message->dispatcher->dispatch(message, listeners);
		
		
		return NULL;
	}
	
	void ConcreteDispatcher::dispatch(Message* message)
	{
		//async call per listener. Typically one except push requests
		message->dispatcher = this;
		this->_threadBoss.createTask((void*)message, &init_thread_request);
		//std::vector<RouteListener*>* listeners = this->_collection.getRouteListeners(message->channel);  
		
		//delete message;
		//this->dispatch(message, listeners);
	}                                 
	
	Request* ConcreteDispatcher::request(Message* data, RequestMiddleware* middleware)
	{                                     
		return new Request(data, middleware, this->router);
	}
	
	void ConcreteDispatcher::addRouteListener(RouteListener* listener)
	{                    
		this->_collection.addRouteListener(listener);
	}          
	
	Message* Router::request(std::string channel)
	{                                                     
		return new Message(Parser::parseChannel(channel), this);
	}
	
	
	void Router::on(std::string route, PullCallback* callback)
	{                                          
		this->on<PullCallback, PullRouteListener, PullDispatcher>(route, callback, this->_puller);
	}
	
	void Router::on(std::string route, PushCallback* callback)
	{                                                                   
		this->on<PushCallback, PushRouteListener, PushDispatcher>(route, callback, this->_pusher);                                 
	};     
	
	void Router::require(std::vector<Bean*>& beans)
	{
		for(int i = beans.size(); i--;)
		{
			beans[i](this);
		}
	}                   
	
	void Router::require(Bean* bean)
	{
		bean(this);
	}
	
	/**
	 */
	
    template<class T, class U, class V>
	void Router::on(std::string route, T* callback, V* dispatcher)
	{
		std::vector<RouteExpression*> expressions;
		
		Parser::parseRoute(route, expressions);
		
		
		for(int i = expressions.size(); i--;)
		{                                       
			dispatcher->addRouteListener(new U(expressions[i], callback));
		}
	}   
	
	void Router::push(Message* data)
	{
		this->_pusher->dispatch(data);  
	}   
	
	void Router::pull(Message* data)
	{
		this->_puller->dispatch(data);
	}
};

