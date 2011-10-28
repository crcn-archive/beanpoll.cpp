#include "tag.h"

void* Beanpole::StringTag::value()
{
	return (void*) &this->_value;
}                                            

void* Beanpole::NumberTag::value()
{
	return (void*)0;
}

void* Beanpole::BooleanTag::value()
{
	return (void*) &this->_value;
}