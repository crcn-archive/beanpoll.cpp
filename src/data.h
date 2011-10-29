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
		PushCallback* _pullCallback;
		
	public:
		ChannelExpression* channel;                                                           
		Router* router;   
		
		/**
		 */
		
		Data(ChannelExpression* channel, Router* router):channel(channel), router(router) { };     
		
		/**
		 */
		
		Data* setData(void* data);
		
		/**
		 */
		
		void* getData(); 
		
		/**
		 */
		
		Data* pull(PushCallback* callback);
		
		/**
		 */
		
		Data* push(void* data);       
		
		/**
		 */
		
		~Data()
		{                                        
			delete this->channel;
		}
		
		
	};
};      

#endif