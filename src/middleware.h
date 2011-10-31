#ifndef MIDDLEWARE_H_
#define MIDDLEWARE_H_ 

#include "linked_list.h"       
#include "listener.h"   
#include "expressions.h"
      
namespace Beanpole
{               
	
	class ConcreteDispatcher;    
	 
	class RequestMiddleware: public LinkedList<RequestMiddleware>
	{
	public:       
		
		/**
		 */
		
		RequestMiddleware(ChannelExpression* channel, RouteListener* listener):
		channel(channel),
		listener(listener) { };
		
		/**                     
		 * the "middleware" which handles a given request
		 */
		
		RouteListener* listener;   
		
		/**                       
		 * channel expression tied to the given listener e.g: /hello/:name, and /hello/world
		 */
		
		ChannelExpression* channel;
		              
		
		/**
		 * moves to the next middleware item
		 */
		bool next();                        
		
		/**
		 * TRUE if there's sibling middleware
		 */
		
		bool hasNext();    
		
		
		/**
		 * expands listeners middleware
		 */
		
		static RequestMiddleware* expand(ChannelExpression* channel, RouteListener* listener, ConcreteDispatcher* dispatcher);
	};
};

#endif