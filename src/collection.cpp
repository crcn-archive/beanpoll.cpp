#include "collection.h"             

namespace Beanpole
{                     
	template<class ListenerClass>
	void Collection<ListenerClass>::addRouteListener(ListenerClass* listener)
	{
		this->getTree(listener->getRoute()->channel)->listeners.push_back(listener);

	}
             
	template<class ListenerClass>
	void Collection<ListenerClass>::removeRouteListener(ListenerClass* listener)
	{
	 //TODO   
	}                                
                             
	template<class ListenerClass>
	std::vector<ListenerClass*>* Collection<ListenerClass>::getRouteListeners(ChannelExpression* channel)
	{
		//TODO      
		return &this->getTree(channel)->listeners;
	}        
                                                 
	template<class ListenerClass>
	RouteTree<ListenerClass>* Collection<ListenerClass>::getTree(ChannelExpression* channel, bool find)
	{
		RouteTree<ListenerClass>* currentTree = this->_tree;

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

        

