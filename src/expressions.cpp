#include "expressions.h"       
#include "utils.h"      

namespace Beanpole
{
	ChannelExpression::~ChannelExpression()
	{                                           
		deleteInVector(&this->paths);     
		this->paths.clear();
	}

	Tag* RouteExpression::getTag(std::string name)
	{                                               
		return this->_tags[name];
	}                 


	Tag* RouteExpression::addTag(std::string name, Tag* tag)
	{
		return this->_tags[name] = tag;
	}                                

	bool RouteExpression::hasTag(std::string name)
	{
		return !!this->getTag(name);
	}
};

