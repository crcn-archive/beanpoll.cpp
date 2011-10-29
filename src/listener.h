#ifndef LISTENER_H_
#define LISTENER_H_   

#include "expressions.h"

namespace Beanpole
{                      
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
		          
		void onRequest();    
		
		/**
		 */
		            
		RouteExpression* getRoute()
		{
			return this->_route;
		}
		
	}; 
	
	
	class PullRouteListener: public RouteListener
	{                             
	};
};

#endif