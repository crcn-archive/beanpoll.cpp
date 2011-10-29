#ifndef LISTENER_H_
#define LISTENER_H_   

#include "expressions.h"
#include "callbacks.h"

namespace Beanpole
{                        
	class Request;
	
	class RouteListener
	{   
	private:
		RouteExpression* _route;
		
	public:                                               
		
		/**
		 */
		
		RouteListener(RouteExpression* route): _route(route) { };       
		
		/**
		 */
		          
		virtual void onRequest(Request* request) = 0;    
		
		/**
		 */
		            
		RouteExpression* getRoute()
		{
			return this->_route;
		}
		
	}; 
	
	
	class PullRouteListener: public RouteListener
	{                      
	public:
		PullRouteListener(RouteExpression* route, PullCallback* callback): RouteListener(route), _callback(callback) { }; 
		
		
    private:
		PullCallback* _callback;
	};                          
	
	class PushRouteListener: public RouteListener
	{      
	public:
		PushRouteListener(RouteExpression* route, PushCallback* callback): RouteListener(route), _callback(callback) { };  
		
		void onRequest(Request* request);        

	private:
		PushCallback* _callback;
	};
};

#endif