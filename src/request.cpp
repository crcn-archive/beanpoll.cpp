     
#include "listener.h" 
#include "request.h"
#include "router.h"        
#include "utils.h"                        

namespace Beanpole
{                  
	template<class ListenerClass, class RequestClass>
	void RequestMiddleware<ListenerClass, RequestClass>::onRequest(RequestClass* request)
	{                                                 
		this->listener->onRequest(request);  
	}
                                                             
	template<class ListenerClass, class RequestClass>
	Request<ListenerClass, RequestClass>::Request(Data* data, ListenerClass* listener, ConcreteDispatcher< ListenerClass, RequestClass >* dispatcher):
	data(data),
	dispatcher(dispatcher),
	_previousMiddleware(NULL)
	{                   
		this->addMiddleware(data->channel, listener);
	};        
     
	
	template<class ListenerClass, class RequestClass>
	Request<ListenerClass, RequestClass>::~Request()
	{           
		//there's a chance that the previous middleware exists - at the end 
		if(this->_previousMiddleware) delete this->_previousMiddleware;       


		//data's no longer needed.      
		delete this->data;                                    
	};                                       
    
	template<class ListenerClass, class RequestClass>
	void Request<ListenerClass, RequestClass>::addMiddleware(ChannelExpression* channel, ListenerClass* listener)
	{                                                                   
		ThruExpression* currentMiddleware = listener->getRoute()->thru;         

		std::vector<ThruExpression*> thru;  


		this->_middleware.push_back(new RequestMiddleware<ListenerClass, RequestClass>(channel, listener));


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

			std::vector<ListenerClass *>* middleware = this->dispatcher->_collection.getRouteListeners(currentMiddleware->channel);

			for(int j = 0, jn = middleware->size(); j < jn; j++)
			{
				this->addMiddleware(currentMiddleware->channel, (*middleware)[j]);
			}
		}
	}
     
	template<class ListenerClass, class RequestClass>
	bool Request<ListenerClass, RequestClass>::hasNext()
	{
		return !!this->_middleware.size();
	}
                   
	template<class ListenerClass, class RequestClass>
	bool Request<ListenerClass, RequestClass>::next()
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
			this->_previousMiddleware->onRequest((RequestClass*)this);     

			return true;
		}               

		return false; 
	}
};

