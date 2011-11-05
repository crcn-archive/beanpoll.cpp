#ifndef Beanpoll_ROUTER_H_
#define Beanpoll_ROUTER_H_   

#include "callbacks.hpp"    
#include "message.hpp"      
#include "collection.hpp"     
#include "listener.hpp" 
#include "parser.hpp"       
#include "request.hpp"      
#include "plugin.hpp"
#include "threading/thread_boss.hpp"

namespace Beanpoll
{                     
	
	class ConcreteDispatcher
	{
	public:
		
		/**
		 */
		
		ConcreteDispatcher(Router* router): router(router) {};
		
		/**
		 */
		
		void dispatch(Message* data); 
		
		/**
		 */
		
		void dispatch(Message* data, std::vector<RouteListener*>* listeners);   
		
		
		/**
		 */
		
		void addRouteListener(RouteListener* listener);   
		
		/**
		 */
		
		friend class RequestMiddleware; 
		
		/**
		 */
		
		Collection _collection;	
		
		/**
		 */
		
		Router* router;
		
	private:  
		ThreadBoss _threadBoss;  
		
		
		static char cleanupRequest(Request*);
		
	protected:             
		Request* request(Message* data, RequestMiddleware* middleware);  
		
		
	};  
	
	
	class PullDispatcher : public ConcreteDispatcher 
	{                         
	public:
		PullDispatcher(Router* router): ConcreteDispatcher(router){};                            
	};
	
	class PushDispatcher: public ConcreteDispatcher 
	{                   
	public:
		PushDispatcher(Router* router): ConcreteDispatcher(router){};
	};
	
	class Router 
	{   
		 
		
	public:        
		
		/**
		 */
		
		Router(): _pusher(new PushDispatcher(this)), _puller(new PullDispatcher(this)) { };
		
		/**
		 */
		
		Message* request(std::string route);   
		
		
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
		
		
	private:
		
		PushDispatcher* _pusher;
		PullDispatcher* _puller;   
	};
};

#endif