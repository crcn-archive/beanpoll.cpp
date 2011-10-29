#ifndef REQUEST_H_
#define REQUEST_H_   
  
#include "data.h"    
#include "listener.h"        
#include "expressions.h"
#include <iostream>
#include <vector>

namespace Beanpole
{   
	class ConcreteDispatcher; 
	class Request;     
	
	class RequestMiddleware
	{
	public:
		
		RouteListener* listener;
		ChannelExpression* channel;
		
		RequestMiddleware(ChannelExpression* channel, RouteListener* listener):
		channel(channel),
		listener(listener){ };
		
	void onRequest(Request*);	
	};
	
	
	
	
	class Request
	{                                                               
	public:         
		
		Data* data;       
		ConcreteDispatcher* dispatcher;
		
		
		Request(Data* data, RouteListener* listener, ConcreteDispatcher* dispatcher);   
		
		bool next();
		
		bool hasNext(); 
		
	private:
		
		std::vector<RequestMiddleware*> _middleware;
		
		void addMiddleware(ChannelExpression* channel, RouteListener* listener);
		
	};
	
	class PushRequest: public Request
	{
		
	};
	
	
	class PullRequest: public Request
	{
		
	};
};      

#endif