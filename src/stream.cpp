#include "stream.hpp"

namespace Beanpoll
{
	
	
	ConcreteRequestStream::ConcreteRequestStream(void*(*reader)(void*), void* data)
	{   
		this->_reader = reader;
		this->_data = data;   
	}         
	
	void* ConcreteRequestStream::read()
	{
		return this->_reader(this->_data);
	}
	
	
};