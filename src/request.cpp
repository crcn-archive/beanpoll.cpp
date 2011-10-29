     
#include "listener.h" 
#include "request.h"
#include "router.h"        
#include "utils.h"     

void Beanpole::RequestMiddleware::onRequest(Beanpole::Request* request)
{                                                 
	this->listener->onRequest(request);  
}

Beanpole::Request::Request(Beanpole::Data* data, Beanpole::RouteListener* listener, Beanpole::ConcreteDispatcher* dispatcher):
data(data),
dispatcher(dispatcher),
_previousMiddleware(NULL)
{                   
	this->addMiddleware(data->channel, listener);
};        

Beanpole::Request::~Request()
{           
	//there's a chance that the previous middleware exists - at the end 
	if(this->_previousMiddleware) delete this->_previousMiddleware;       
	                                 
	
	//data's no longer needed.      
	delete this->data;                                    
};                                       

void Beanpole::Request::addMiddleware(Beanpole::ChannelExpression* channel, Beanpole::RouteListener* listener)
{                                                                   
	Beanpole::ThruExpression* currentMiddleware = listener->getRoute()->thru;         
	
	std::vector<Beanpole::ThruExpression*> thru;  
	                                     
	
	this->_middleware.push_back(new Beanpole::RequestMiddleware(channel, listener));
	        
	
	//reverse
	while(currentMiddleware)
	{
		thru.push_back(currentMiddleware);
		currentMiddleware = currentMiddleware->thru;
	}       
	         
	
	//now we can add the middleware                  
	for(int i = thru.size(); i--;)
	{
		currentMiddleware = thru[i];  
		
		std::vector<RouteListener*>* middleware = this->dispatcher->_collection.getRouteListeners(currentMiddleware->channel);
  
		for(int j = 0, jn = middleware->size(); j < jn; j++)
		{
			this->addMiddleware(currentMiddleware->channel, (*middleware)[j]);
		}
	}
}

bool Beanpole::Request::hasNext()
{
	return !!this->_middleware.size();
}

bool Beanpole::Request::next()
{   
	if(this->_previousMiddleware)
	{                                 
		delete this->_previousMiddleware;    
		this->_previousMiddleware = NULL;
	}           
	
	if(this->_middleware.size())
	{                                                  
	    this->_previousMiddleware = this->_middleware.back();                            
		                             
		
		//remove from the current middleware since we've used it.
		this->_middleware.pop_back();    
		          
		//notify the listener
		this->_previousMiddleware->onRequest(this);     
		
		return true;
	}               
	
	return false; 
}