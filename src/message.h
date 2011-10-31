#ifndef DATA_H_
#define DATA_H_     

#include "expressions.h"   
#include "callbacks.h"  
#include "stream.h"
     
namespace Beanpole
{   
	class Router;          
	
	class Message
	{      
	private:
		RequestStream* _stream;                     
		StreamCallback* _callback;
		
	public:
		ChannelExpression* channel;                                                           
		Router* router;   
		
		/**
		 */
		
		Message(ChannelExpression* channel, Router* router):channel(channel), router(router), _callback(NULL) { };     
		
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
		
		~Message()
		{                                        
			delete this->channel;
		}
		
		
	};
};      

#endif