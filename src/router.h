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
	                          
	template<class ListenerClass, class RequestClass>
	class ConcreteDispatcher
	{
	public:
		ConcreteDispatcher(){};
		
		void dispatch(Data* data); 
		void dispatch(Data* data, std::vector<ListenerClass*>* listeners);   
		void addRouteListener(ListenerClass* listener);  
			Collection<ListenerClass> _collection; 
		
	private:                                      
		ThreadPool _threadPool;     
		
	protected:             
		RequestClass* request(Data* data, ListenerClass* listener);  
		
		                
	};  
	               
	
	class PullDispatcher : public ConcreteDispatcher<PullRouteListener, PullRequest> 
	{                         
	public:
		PullDispatcher(): ConcreteDispatcher<PullRouteListener, PullRequest>(){};                            
	};
	
	class PushDispatcher: public ConcreteDispatcher< PushRouteListener, PushRequest> 
	{                   
	public:
		PushDispatcher(): ConcreteDispatcher<PushRouteListener, PushRequest>(){};
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
		
		/**
		 */
		                  
	    template<class T, class U>
		void on(std::string route, T* callback);
	};
};

#endif