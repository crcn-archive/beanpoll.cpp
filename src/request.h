#ifndef REQUEST_H_
#define REQUEST_H_   
  
#include "message.h"    
#include "listener.h"
#include "middleware.h"     
#include "expressions.h"  
#include "stream.h"
#include "utils.h"
#include <iostream>
#include <vector>        

namespace Beanpole
{   
	class ConcreteDispatcher; 
	class Request;     
	
	/*class RequestMiddleware
	{
	public:
		
		RouteListener* listener;
		ChannelExpression* channel;           
		
		RequestMiddleware(ChannelExpression* channel, RouteListener* listener):
		channel(channel),
		listener(listener){ };  
		
		~RequestMiddleware()
		{                                          
		}
		
	void onRequest(Request*);	
	};*/
	
	
	
	
	class Request
	{                                                               
	public:         
		
		/**
		 * the data passed in the request
		 */
		
		Message* message;                 
		
		/**
		 * the dispatcher which owns all the routes ~ dispatched *this* request
		 */
		
		// ConcreteDispatcher* dispatcher;            
		
		/**   
		 * The previous middleware - deleted on each request
		 */
		
		// RequestMiddleware* _previousMiddleware;
		
		
		Request(Message* data, RequestMiddleware* middleware);
		bool next();        
		bool hasNext();     
		~Request();
		
	private:
		
		RequestMiddleware* _currentMiddleware;                                                
		
	};                  
	
	     
	
	
	             
	
	class StreamedRequest: public Request
	{
	public:                             
		void end();           
		void end(void* chunk);  
		void end(RequestStream* stream);     
		
		void* read();
		// void end(void*(callback*)(void*), void* data);   
	};
	
	
	class PushRequest: public StreamedRequest
	{
		
	};
	
	
	class PullRequest: public StreamedRequest
	{
		
	};
};    

// void Beanpole::deleteInVector(std::vector<Beanpole::RequestMiddleware*>*);  

#endif