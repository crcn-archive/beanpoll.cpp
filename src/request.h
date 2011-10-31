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
		
		~RequestMiddleware()
		{                                          
		}
		
	void onRequest(Request*);	
	};
	
	
	
	
	class Request
	{                                                               
	public:         
		
		/**
		 * the data passed in the request
		 */
		
		Data* data;                 
		
		/**
		 * the dispatcher which owns all the routes ~ dispatched *this* request
		 */
		
		ConcreteDispatcher* dispatcher;            
		
		/**   
		 * The previous middleware - deleted on each request
		 */
		
		RequestMiddleware* _previousMiddleware;
		
		
		Request(Data* data, RouteListener* listener, ConcreteDispatcher* dispatcher);
		bool next();        
		bool hasNext();     
		~Request();
		
	private:
		
		std::vector<RequestMiddleware*> _middleware;
		
		void addMiddleware(ChannelExpression* channel, RouteListener* listener);
		
	};                  
	
	class ConcreteRequestStream
	{   
	public:  
		ConcreteRequestStream(void*(*reader)(void*), void* data);    
		                        
		void* read();          
	
	private:
		void*(*_reader)(void*);   
		void* _data;
	};
	
	class RequestStream : public ConcreteRequestStream
	{         
	public:                                          
		   
		RequestStream():ConcreteRequestStream(&RequestStream::readData, NULL) {};
		RequestStream(void* data):ConcreteRequestStream(&RequestStream::readData, data) {};    
		
	private:  
		
		
		
		/**
		 */
		
		static void* readData(void* data)
		{
			return data;
		}
	};     
	
	
	             
	
	class StreamedRequest: public Request
	{
	public:                             
		void end();           
		void end(void* chunk);  
		void end(RequestStream* stream);
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