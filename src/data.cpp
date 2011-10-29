#include "data.h"     
#include "router.h"

Beanpole::Data* Beanpole::Data::setData(void* data)
{
	this->_data = data;     
	return this;
}               

void* Beanpole::Data::getData()
{
	return this->_data;
}                      

Beanpole::Data* Beanpole::Data::push(void* data)
{
	this->setData(data);
	
	this->router->push(this);
}                            


Beanpole::Data* Beanpole::Data::pull(PushCallback* callback)
{                      
	this->_pullCallback = callback;
}