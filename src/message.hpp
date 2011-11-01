#ifndef DATA_H_
#define DATA_H_     

#include "expressions.hpp"   
#include "callbacks.hpp"  
#include "stream.hpp"
     
namespace Beanpoll
{   
	class Router;  
	class ConcreteDispatcher;
	
	class Message
	{      
	private:                
		
		/**              
		 * stream of data for the message - e.g: files, objects, etc.
		 */
		
		RequestStream* _stream;                                      
		
		/**
		 * the callback function for a given response - used for PULL requests
		 */
		
		StreamCallback* _callback;
		
	public:                                                                   
		
		/**                                     
		 * the target channel making a request to
		 */
		
		ChannelExpression* channel;   
		
		/**
		 * the router which handles all requests
		 */
		                                                        
		Router* router; 
		
		/**
		 */
		
		ConcreteDispatcher* dispatcher;
		
		/**
		 */
		
		Message(ChannelExpression* channel, Router* router):
		channel(channel), 
		router(router), 
		_callback(NULL),
	    _stream(NULL) { };         

		
		/**     
		 */
		
		Message* setData(void* data); 
		
		/**
		 */
		
		Message* setData(void*(*callback)(void*),void* data); 
		
		/**
		 */
		
		Message* setData(RequestStream* stream);
		
		/**
		 */
		
		RequestStream* getStream(); 
		
		/**
		 */
		
		Message* setCallback(StreamCallback* callback);
		
		/**
		 */
		
		StreamCallback* getCallback();
		
		/**
		 */
		
		Message* pull(StreamCallback* callback);      
		
		
		/**
		 */
		
		Message* pull(void* data, StreamCallback* callback);
		
		/**
		 */
		
		Message* pull(void*(*callback)(void*),void* data, StreamCallback* callback);   
		
		/**
		 */
		
		Message* push(void* data);     
		
		/**
		 */
		
		Message* push(void*(*callback)(void*), void* data);
		/**
		 */
		
		Message* clone();  
		
		/**
		 */
		
		~Message();
		
		
	};
};      

#endif