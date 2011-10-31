#include "data.h"     
#include "router.h"  

namespace Beanpole
{
	Data* Data::setData(void* data)
	{
		this->_data = data;     
		return this;
	}               

	void* Data::getData()
	{
		return this->_data;
	}           
	
	Data* Data::setCallback(StreamCallback* callback)
	{
		this->_callback = callback;   
		return this;
	}                                  
	
	StreamCallback* Data::getCallback()
	{
		return this->_callback;
	}

	Data* Data::push(void* data)
	{
		this->setData(data);

		this->router->push(this);      
		
		return this;
	}                            


	Data* Data::pull(StreamCallback* callback)
	{                               
		this->setCallback(callback);    
		this->router->pull(this);
		return this;
	}  
	
	Data* Data::pull(void* data, StreamCallback* callback)
	{              
		this->setData(data);                           
		return this->pull(callback);
	}       
	
	Data* Data::clone()
	{                   
		return (new Data(this->channel->clone(), this->router))->
		setData(this->getData())->
		setCallback(this->getCallback());
	}
}

