#ifndef DATA_H_
#define DATA_H_     

#include "expressions.h"   
#include "callbacks.h"
     
namespace Beanpole
{   
	class Router;          
	
	class Data
	{      
	private:
		void* _data;                     
		StreamCallback* _callback;
		
	public:
		ChannelExpression* channel;                                                           
		Router* router;   
		
		/**
		 */
		
		Data(ChannelExpression* channel, Router* router):channel(channel), router(router), _callback(NULL) { };     
		
		/**
		 */
		
		Data* setData(void* data);
		
		/**
		 */
		
		void* getData(); 
		
		/**
		 */
		
		Data* setCallback(StreamCallback* callback);
		
		/**
		 */
		
		StreamCallback* getCallback();
		
		/**
		 */
		
		Data* pull(StreamCallback* callback);      
		
		
		/**
		 */
		
		Data* pull(void* data, StreamCallback* callback);
		
		/**
		 */
		
		Data* push(void* data);     
		
		/**
		 */
		
		Data* clone();  
		
		/**
		 */
		
		~Data()
		{                                        
			delete this->channel;
		}
		
		
	};
};      

#endif