#ifndef LISTENER_H_
#define LISTENER_H_   

#include "expressions.h"
#include "callbacks.h"

namespace Beanpole
{                                                 
	class PullRequest;
	class PushRequest;          
	     
	
	
	            
	template<class RequestClass, class CallbackType>
	class RouteListener
	{   
	private:
		RouteExpression* _route;  
		CallbackType* _callback;
		
	public:                                               
		
		/**
		 */
		
		RouteListener(RouteExpression* route, CallbackType* callback): _route(route), _callback(callback) { };       
		
		/**
		 */
		                                
		
		void onRequest(RequestClass* request);    
		
		/**
		 */
		            
		RouteExpression* getRoute()
		{
			return this->_route;
		}
		
	}; 
	                 
	    
	
	class PullRouteListener: public RouteListener<PullRequest, PullCallback>
	{         
	public:        
		PullRouteListener(RouteExpression* route, PullCallback* callback): RouteListener<PullRequest, PullCallback>(route, callback){};  
	};                          
	
	class PushRouteListener: public RouteListener<PushRequest, PushCallback>
	{                                                            
	public:        
		PushRouteListener(RouteExpression* route, PushCallback* callback): RouteListener<PushRequest, PushCallback>(route, callback){};   
	}; 
};

#endif