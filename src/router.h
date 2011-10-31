#ifndef BEANPOLE_ROUTER_H_
#define BEANPOLE_ROUTER_H_   
                   
#include "callbacks.h"    
#include "message.h"      
#include "collection.h"     
#include "listener.h" 
#include "parser.h"       
#include "request.h"      
#include "plugin.h"
#include "threading/thread_pool.h"

namespace Beanpole
{                     
	
	class ConcreteDispatcher
	{
	public:
		ConcreteDispatcher(){};
		
		void dispatch(Message* data); 
		void dispatch(Message* data, std::vector<RouteListener*>* listeners);   
		void addRouteListener(RouteListener* listener);   
		friend class RequestMiddleware; 
		
	private:
		Collection _collection;	  
		ThreadPool _threadPool;     
		
	protected:             
		Request* request(Message* data, RequestMiddleware* middleware);  
		
		                
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
		
		Message* request(const char* route);   
		
		/**
		 */
		
		void push(Message* data);
		
		/**
		 */
		
		void pull(Message* data);
		                                                         
		/**
		 */
		
		void on(std::string route, PullCallback* callback);     
		
		/**
		 */
		
		void on(std::string route, PushCallback* callback);   
		
		/**
		 */
		
		void require(std::vector<Bean*>& beans);    
		
		/**
		 */
		
		void require(Bean* bean);
		
		
		/**
		 */
		                  
	    template<class T, class U, class V>
		void on(std::string route, T* callback, V* dispatcher);
	};
};

#endif