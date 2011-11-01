#include "message.hpp"     
#include "router.hpp"  

namespace Beanpoll
{   
	Message::~Message()
	{
		delete this->channel;
		if(this->_stream) delete this->_stream;
	}                     
	
	
	Message* Message::setData(void* data)
	{
		this->_stream = new RequestStream(data);     
		return this;
	}      
	
	Message* Message::setData(void*(*reader)(void*), void* data)
	{
		// this->_stream = new RequestStream(reader, data);  
		return this;
	}
	
	Message* Message::setData(RequestStream* stream)
	{
		this->_stream = stream;  
		return this;
	}         
	
	RequestStream* Message::getStream()
	{
		return this->_stream;
	} 
	
	
	
	Message* Message::setCallback(StreamCallback* callback)
	{
		this->_callback = callback;   
		return this;
	}    
	
	bool Message::hasCallback()
	{
		return !!this->_callback;
	}
	
	StreamCallback* Message::getCallback()
	{
		return this->_callback;
	}
	
	Message* Message::push(void* data)
	{
		this->setData(data);       
		this->router->push(this);       
		return this;
	}         
	
	Message* Message::push(void*(*callback)(void*), void* data)
	{
		this->setData(callback, data);
		this->router->push(this);
		return this;
	}                   
	
	
	Message* Message::pull(StreamCallback* callback)
	{                               
		this->setCallback(callback);    
		this->router->pull(this);
		return this;
	}  
	
	Message* Message::pull(void* data, StreamCallback* callback)
	{              
		this->setData(data);                           
		return this->pull(callback);
	}   
	
	Message* Message::pull(void*(*reader)(void*), void* data, StreamCallback* callback)
	{              
		this->setData(reader, data);                           
		return this->pull(callback);
	}    
	
	Message* Message::clone()
	{                   
		return (new Message(this->channel->clone(), this->router))->   
		
		//TODO - use copied stream 
		setData(this->getStream()->read())->
		setCallback(this->getCallback());
	}
}

