#include "middleware.hpp"

namespace Beanpoll
{                           
	
	RequestMiddleware* RequestMiddleware::expand(ChannelExpression* channel, RouteListener* listener, ConcreteDispatcher* dispatcher)
	{                                                          
		ThruExpression* currentMiddleware = listener->getRoute()->thru;         
		
		
		RequestMiddleware* last = new RequestMiddleware(channel, listener);                 
		RequestMiddleware* current = last;                                     
		
		
		while(currentMiddleware)
		{                                                          
			
			std::vector<RouteListener*>* middleware = dispatcher->_collection.getRouteListeners(currentMiddleware->channel);    
			
			
			
			for(int j = 0, jn = middleware->size(); j < jn; j++)
			{      
				current = RequestMiddleware::expand(currentMiddleware->channel, (*middleware)[j], dispatcher);  
				
				last->addPrevSibling(current->getLastSibling());
				
				last = current->getFirstSibling();     
			}      
			
			currentMiddleware = currentMiddleware->thru;
		}              
		
		
		return last->getFirstSibling();
	}
};