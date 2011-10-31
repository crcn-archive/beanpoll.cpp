#include "middleware.h"

namespace Beanpole
{   
	bool RequestMiddleware::next()
	{
		return false;
	}                
	
	bool RequestMiddleware::hasNext()
	{
		return false;
	}      
	
	
	RequestMiddleware* RequestMiddleware::expand(ChannelExpression* channel, RouteListener* listener, ConcreteDispatcher* dispatcher)
	{                                                          
		ThruExpression* currentMiddleware = listener->getRoute()->thru;         
                                            
		
		RequestMiddleware* last = new RequestMiddleware(channel, listener);
                     

		std::vector<ThruExpression*> thru;
        

		//reverse the middleware. last = first.
		while(currentMiddleware)
		{
			thru.push_back(currentMiddleware);
			currentMiddleware = currentMiddleware->thru;
		}         
		
		
		RequestMiddleware* first = last;  
		RequestMiddleware* current = NULL;   
		                                 


		//now we can add the middleware                  
		for(int i = thru.size(); i--;)
		{
			currentMiddleware = thru[i];                           
std::cout << (currentMiddleware->channel->value) << std::endl;

			std::vector<RouteListener*>* middleware = dispatcher->_collection.getRouteListeners(currentMiddleware->channel);
                                                                                     
			
			for(int j = 0, jn = middleware->size(); j < jn; j++)
			{                                          
				current = RequestMiddleware::expand(currentMiddleware->channel, (*middleware)[j], dispatcher);  
				       
				last->setFirstSibling(current);
				last = current;
			}
		}    
		       
		return first;
	}
};