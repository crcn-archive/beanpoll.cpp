
#include "listener.hpp" 
#include "request.hpp"
#include "router.hpp"        
#include "utils.hpp"                        

namespace Beanpoll
{
	/*void RequestMiddleware::onRequest(Request* request)
	 {                                                 
	 this->listener->onRequest(request);  
	 }*/
	
	Request::Request(Message* message, RequestMiddleware* middleware, Router* router):
	message(message),
	_currentMiddleware(middleware),
	_firstMiddleware(middleware),
	router(router)
	{    
		
	};   
	
	void Request::onComplete(RequestCompleteCallback* callback)
	{
		this->_completeListeners.add(callback);
	}
	
	Request::~Request()
	{                
		
		//data's no longer needed.      
		delete this->message;   
		
		RequestMiddleware* currentMiddleware = this->_firstMiddleware;
		
		//clean up the middleware
		while(currentMiddleware->getNextSibling())
		{                                             
			delete currentMiddleware->getNextSibling()->remove();
		}   
		
		//final cleanup
		delete currentMiddleware;
	};                                       
	
	
	
	bool Request::hasNext()
	{
		return !!this->_currentMiddleware;
	}
	
	bool Request::next()
	{                                      
		//no more middleware
		if(!this->_currentMiddleware) return false;          
		
		RequestMiddleware* current = this->_currentMiddleware; 
		this->_currentMiddleware = this->_currentMiddleware->getNextSibling();
		
		current->listener->onRequest(this); 
		
		return this->hasNext(); 
	}   
	
	
	void StreamedRequest::end(RequestStream* stream)
	{                
		if(this->message->hasCallback())  this->message->getCallback()(stream); 
		
		delete stream;
		
		this->_completeListeners.notify((Request*)this);
		//if(this->_onComplete) this->_onComplete(this);
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

