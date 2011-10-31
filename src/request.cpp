     
#include "listener.h" 
#include "request.h"
#include "router.h"        
#include "utils.h"                        

namespace Beanpole
{
	/*void RequestMiddleware::onRequest(Request* request)
	{                                                 
		this->listener->onRequest(request);  
	}*/

	Request::Request(Message* message, RequestMiddleware* middleware):
	message(message),
	_currentMiddleware(middleware)
	{                                               
	};        

	Request::~Request()
	{                                   

		//data's no longer needed.      
		delete this->message;                                    
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

