        
                    
#include "request.h"
#include "router.h"  
#include "listener.h"     
#include "utils.h"
#include <iostream>                
#include <vector>   
#include <pthread.h>   
                  

namespace Beanpole
{               
	template<class ListenerClass, class RequestClass>
	void ConcreteDispatcher<ListenerClass, RequestClass>::dispatch(Data* data)
	{
		std::vector<ListenerClass*>* listeners = this->_collection.getRouteListeners(data->channel);    

		ConcreteDispatcher<ListenerClass, RequestClass>::dispatch(data, listeners);
	}                                 


	void* dispatch_threaded_request(void* request)
	{                                                      
		((AbstractRequest*)request)->next(); 
		delete (AbstractRequest*)request;                        
		return NULL;
	}                     

               
	template<class ListenerClass, class RequestClass>
	void ConcreteDispatcher<ListenerClass, RequestClass>::dispatch(Data* data, std::vector<ListenerClass*>* listeners)
	{                         
                            
		for(int i = listeners->size(); i--;)
		{               
			void* val;

			//TODO: check if request is threaded.
			ListenerClass* listener = (*listeners)[i];

			AbstractRequest* request = this->request(data, listener);            
                                                                 

			//async call per listener. Typically one except push requests
			this->_threadPool.createTask((void*)request, &dispatch_threaded_request);
		}
	}        
         
	template<class ListenerClass, class RequestClass>
	RequestClass* ConcreteDispatcher<ListenerClass, RequestClass>::request(Data* data, ListenerClass* listener)
	{                                     
		return new RequestClass(data, listener, this);
	}
              
	template<class ListenerClass, class RequestClass>
	void ConcreteDispatcher<ListenerClass, RequestClass>::addRouteListener(ListenerClass* listener)
	{                    
		this->_collection.addRouteListener(listener);
	}          

	Data* Router::request(const char* channel)
	{          
		return new Data(Parser::parseChannel(channel), this);
	}


	void Router::on(std::string route, PullCallback* callback)
	{                                           
		// this->on<PullCallback, RouteListener<PullRequest> >(route, callback);
	}

	void Router::on(std::string route, PushCallback* callback)
	{                                           
	    // this->on<PushCallback, RouteListener<PushRequest> >(route, callback);  
	};       
	
	template<class T, class U>
	void Router::on(std::string route, T* callback)
	{
		std::vector<RouteExpression*> expressions;

		Parser::parseRoute(route, expressions);

         
		for(int i = expressions.size(); i--;)
		{                                       
			this->_pusher->addRouteListener(new U(expressions[i], callback));
		}
	}

	void Router::push(Data* data)
	{
		this->_pusher->dispatch(data);  
	}   

	void Router::pull(Data* data)
	{
		this->_puller->dispatch(data);
	}
};

