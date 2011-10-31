#ifndef REQUEST_H_
#define REQUEST_H_   
  
#include "message.hpp"    
#include "listener.hpp"
#include "middleware.hpp"     
#include "expressions.hpp"  
#include "stream.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>        

namespace Beanpoll
{   
	class ConcreteDispatcher; 
	class Request;     
	
	
	
	
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
		         
		
		/**   
		 * The previous middleware - deleted on each request
		 */
		
		
		Request(Message* data, RequestMiddleware* middleware);
		bool next();        
		bool hasNext();     
		~Request();
		
	private:
		
		RequestMiddleware* _currentMiddleware;                                                
		RequestMiddleware* _firstMiddleware;
	};                  
	
	     
	
	
	             
	
	class StreamedRequest: public Request
	{
	public:                             
		void end();           
		void end(void* chunk);  
		void end(RequestStream* stream);     
		
		void* read(); 
	};
	
	
	class PushRequest: public StreamedRequest
	{
		
	};
	
	
	class PullRequest: public StreamedRequest
	{
		
	};
};    

#endif