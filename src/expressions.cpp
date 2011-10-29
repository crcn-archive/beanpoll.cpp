#include "expressions.h"       
#include "utils.h"

Beanpole::ChannelExpression::~ChannelExpression()
{                                           
	Beanpole::deleteInVector(&this->paths);     
	this->paths.clear();
}
                                                                      
Beanpole::Tag* Beanpole::RouteExpression::getTag(std::string name)
{                                               
	return this->_tags[name];
}                 
            

Beanpole::Tag* Beanpole::RouteExpression::addTag(std::string name, Beanpole::Tag* tag)
{
	return this->_tags[name] = tag;
}                                
          
bool Beanpole::RouteExpression::hasTag(std::string name)
{
	return !!this->getTag(name);
}