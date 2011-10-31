#ifndef REQUEST_H_
#define REQUEST_H_   
  
#include "data.h"    
#include "listener.h"        
#include "expressions.h"  
#include "utils.h"
#include <iostream>
#include <vector>

namespace Beanpole
{   
	template<class T, class R> class ConcreteDispatcher;        
	      
	
	template<class ListenerClass, class RequestClass>
	class RequestMiddleware
	{
	public:
		
	    ListenerClass* listener;
		ChannelExpression* channel;           
		
		RequestMiddleware(ChannelExpression* channel, ListenerClass* listener):
		channel(channel),
		listener(listener){ };  
		
		~RequestMiddleware()
		{                                          
		}
		
		void onRequest(RequestClass*);	
	};                        
	
	class AbstractRequest
	{
		public:         

			/**
			 * the data passed in the request
			 */

			Data* data;                                                     
                                                                                                                              
			/**
			 */

			virtual bool next() = 0;

			/**
			 */

			virtual bool hasNext() = 0;                                                                   
	};
	
	
	
	         
	template<class ListenerClass, class RequestClass>
	class Request : public AbstractRequest
	{                                                               
	public:         
		
		/**
		 * the data passed in the request
		 */
		
		Data* data;                 
		
		/**
		 * the dispatcher which owns all the routes ~ dispatched *this* request
		 */
		
		ConcreteDispatcher<ListenerClass, RequestClass >* dispatcher;            
		
		/**   
		 * The previous middleware - deleted on each request
		 */
		
		RequestMiddleware<ListenerClass, RequestClass>* _previousMiddleware;
		
		            
		/**
		 */
		
		Request(Data* data, ListenerClass* listener, ConcreteDispatcher< ListenerClass, RequestClass >* dispatcher);   
		
		/**
		 */
		
		bool next();
		
		/**
		 */
		
		bool hasNext();      
		
		/**
		 */
		
		~Request();
		
	private:
		
		/**
		 */
		
		std::vector<RequestMiddleware< ListenerClass, RequestClass >*> _middleware;
		
		/**
		 */
		
		void addMiddleware(ChannelExpression* channel, ListenerClass* listener);
		
	};
	
	class PushRequest: public Request<PushRouteListener, PushRequest >
	{     	          
	public:
		PushRequest(Data* data, PushRouteListener* listener, ConcreteDispatcher< PushRouteListener, PushRequest >* dispatcher):
		Request<PushRouteListener, PushRequest >(data, listener, dispatcher){}; 
	};
	
	
	class PullRequest: public Request< PullRouteListener, PullRequest >
	{    
	public:
		PullRequest(Data* data, PullRouteListener* listener, ConcreteDispatcher< PullRouteListener, PullRequest >* dispatcher):
		Request<PullRouteListener, PullRequest >(data, listener, dispatcher){};
	};
};                                                                                 

#endif