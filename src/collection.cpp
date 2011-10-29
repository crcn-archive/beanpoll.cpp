#include "collection.h"

void Beanpole::Collection::addRouteListener(Beanpole::RouteListener* listener)
{
	this->getTree(listener->getRoute()->channel)->listeners.push_back(listener);
	
}

void Beanpole::Collection::removeRouteListener(Beanpole::RouteListener* listener)
{
 //TODO   
}                                

std::vector<Beanpole::RouteListener*>& Beanpole::Collection::getRouteListeners(Beanpole::ChannelExpression* listener)
{
	//TODO
}        

Beanpole::RouteTree* Beanpole::Collection::getTree(Beanpole::ChannelExpression* channel, bool find)
{
	RouteTree* currentTree = this->_tree;
	
	for(int i = 0, n = channel->paths.size(); i < n; i++)
	{
		Beanpole::PathExpression* path = channel->paths[i];
		
		std::string pathName = path->param ? "_param" : path->value;
		
		currentTree = currentTree->getChild(pathName, !find);
		
		if(!currentTree) currentTree = currentTree->getChild("_param", false);
	}                                                                         
	
	return currentTree;
}        

