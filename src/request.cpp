     
#include "listener.h" 
#include "request.h"
#include "router.h"        
#include "utils.h"                        

namespace Beanpole
{
	void RequestMiddleware::onRequest(Request* request)
	{                                                 
		this->listener->onRequest(request);  
	}

	Request::Request(Message* message, RouteListener* listener, ConcreteDispatcher* dispatcher):
	message(message),
	dispatcher(dispatcher),
	_previousMiddleware(NULL)
	{                   
		this->addMiddleware(message->channel, listener);
	};        

	Request::~Request()
	{           
		//there's a chance that the previous middleware exists - at the end 
		if(this->_previousMiddleware) delete this->_previousMiddleware;       


		//data's no longer needed.      
		delete this->message;                                    
	};                                       

	void Request::addMiddleware(ChannelExpression* channel, RouteListener* listener)
	{                                                                   
		ThruExpression* currentMiddleware = listener->getRoute()->thru;         

		std::vector<ThruExpression*> thru;  


		this->_middleware.push_back(new RequestMiddleware(channel, listener));


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

	bool Request::hasNext()
	{
		return !!this->_middleware.size();
	}

	bool Request::next()
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
	
	 
	
	void StreamedRequest::end(RequestStream* stream)
	{                
		this->message->getCallback()(stream); 
		
		delete stream;
	}                        
	
	           
	void StreamedRequest::end(void* data)
	{
		this->end(new RequestStream(data));
	}
	   
	
	void StreamedRequest::end()
	{                        
		this->end(new RequestStream());
	}            
	
	void* StreamedRequest::read()
	{                
		return this->message->getStream()->read();
	}
};

