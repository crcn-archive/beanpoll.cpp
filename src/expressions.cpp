#include "expressions.hpp"       
#include "utils.hpp"      

namespace Beanpoll
{
	ChannelExpression::~ChannelExpression()
	{                                           
		deleteInVector(&this->paths);     
		this->paths.clear();
	}               
	
	ChannelExpression* ChannelExpression::clone()
	{   
		ChannelExpression* clone = new ChannelExpression();    
		clone->value = this->value;             
		
		cloneVector(&this->paths, &clone->paths);
		
		return clone;
	}                              
	
	PathExpression* PathExpression::clone()
	{
		return new PathExpression(this->value, this->param);
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

