#include "collection.h"             

namespace Beanpole
{
	void Collection::addRouteListener(RouteListener* listener)
	{
		this->getTree(listener->getRoute()->channel)->listeners.push_back(listener);

	}

	void Collection::removeRouteListener(RouteListener* listener)
	{
	 //TODO   
	}                                

	std::vector<RouteListener*>* Collection::getRouteListeners(ChannelExpression* channel)
	{
		//TODO      
		return &this->getTree(channel)->listeners;
	}        

	RouteTree* Collection::getTree(ChannelExpression* channel, bool find)
	{
		RouteTree* currentTree = this->_tree;

		for(int i = 0, n = channel->paths.size(); i < n; i++)
		{
			PathExpression* path = channel->paths[i];

			std::string pathName = path->param ? "_param" : path->value;

			currentTree = currentTree->getChild(pathName, !find);

			if(!currentTree) currentTree = currentTree->getChild("_param", false);
		}                                                                         

		return currentTree;
	}
};

        

