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
	class Router;
	class Request;     
	
	
	
	
	class Request
	{                                                               
	public:         
		
		/**
		 * the data passed in the request
		 */
		
		Message* message;                 
		
		/**
		 * routes all requests. Useful for calling requests within requests
		 */
		
		Router* router;
		
		/**
		 */
		
		Request(Message* data, RequestMiddleware* middleware, Router* router);
		bool next();        
		bool hasNext();     
		~Request();
		
	private:
		
		/**
		 * the current middleware (listener) in the request chain
		 */
		
		RequestMiddleware* _currentMiddleware;                   
		
		/**
		 * First item in the middleware - used for cleaning up since it's a linked list
		 */
		
		RequestMiddleware* _firstMiddleware;
	};                  
	
	
	
	
	
	
	class StreamedRequest: public Request
	{
	public:      
		
		/**
		 */
		
		void end();           
		
		/**
		 */
		
		void end(void* chunk);  
		
		/**
		 */
		
		void end(RequestStream* stream);     
		
		/**
		 */
		
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