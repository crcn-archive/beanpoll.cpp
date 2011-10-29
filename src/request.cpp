     
#include "listener.h" 
#include "request.h"
#include "router.h"             

void Beanpole::RequestMiddleware::onRequest(Beanpole::Request* request)
{                                                 
	this->listener->onRequest(request);  
}

Beanpole::Request::Request(Beanpole::Data* data, Beanpole::RouteListener* listener, Beanpole::ConcreteDispatcher* dispatcher):
data(data),
dispatcher(dispatcher)
{                   
	this->addMiddleware(data->channel, listener);
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
	if(this->_middleware.size())
	{   
		RequestMiddleware* middleware = this->_middleware[this->_middleware.size()-1];                            
		
		this->_middleware.pop_back();    
		
		middleware->onRequest(this);
		
		return true;
	}               
	
	return false; 
}