#ifndef BEANPOLE_ROUTER_H_
#define BEANPOLE_ROUTER_H_   
                   
#include "callbacks.h"    
#include "data.h"      
#include "collection.h"     
#include "listener.h" 
#include "parser.h"       
#include "request.h"      
#include "threading/thread_pool.h"

namespace Beanpole
{                     
	
	class ConcreteDispatcher
	{
	public:
		ConcreteDispatcher(): _threadPool(new ThreadPool()){};
		
		void dispatch(Data* data); 
		void dispatch(Data* data, std::vector<RouteListener*>* listeners);   
		void addRouteListener(RouteListener* listener);   
		friend class Request; 
		
	private:
		Collection _collection;	  
		ThreadPool* _threadPool;     
		
	protected:             
		Request* request(Data* data, RouteListener* listener);  
		
		                
	};  
	               
	
	class PullDispatcher : public ConcreteDispatcher 
	{                         
	public:
		PullDispatcher(): ConcreteDispatcher(){};                            
	};
	
	class PushDispatcher: public ConcreteDispatcher 
	{                   
	public:
		PushDispatcher(): ConcreteDispatcher(){};
	};
	
	class Router 
	{   
		
	private:
		
		PushDispatcher* _pusher;
		PullDispatcher* _puller;
		   
	public:        
		
		/**
		 */
		
		Router(): _pusher(new PushDispatcher()), _puller(new PullDispatcher()) { };
		
		/**
		 */
		
		Data* request(const char* route);   
		
		/**
		 */
		
		void push(Data* data);
		
		/**
		 */
		
		void pull(Data* data);
		                                                         
		/**
		 */
		
		void on(std::string route, PullCallback* callback);     
		
		/**
		 */
		
		void on(std::string route, PushCallback* callback);
	};
};

#endif