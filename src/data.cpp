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

	Data* Data::push(void* data)
	{
		this->setData(data);

		this->router->push(this);
	}                            


	Data* Data::pull(PushCallback* callback)
	{                      
		this->_pullCallback = callback;
	}
}

