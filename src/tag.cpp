#include "tag.hpp"          

namespace Beanpoll
{
	void* StringTag::value()
	{ 
		return (void*) &this->_value;
	}                                            

	void* NumberTag::value()
	{
		return (void*)0;
	}

	void* BooleanTag::value()
	{
		return (void*) &this->_value;
	}
};

