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
		return &this->getTree(channel, true)->listeners;
	}       
	
	RouteTree* RouteTree::getChild(std::string path, bool create)		
	{                                     
		
		if(!this->_children[path] && create)
		{        
			this->_children[path] = new RouteTree(path);
		}                                                                                                           
		
		return this->_children[path];
	} 

	RouteTree* Collection::getTree(ChannelExpression* channel, bool find)
	{
		RouteTree* currentTree = this->_tree;
		RouteTree* newTree = NULL;

		for(int i = 0, n = channel->paths.size(); i < n; i++)
		{
			PathExpression* path = channel->paths[i];

			std::string pathName = path->param ? "_param" : path->value;    

			newTree = currentTree->getChild(pathName, !find); 
			                                               
                                 
			if(!newTree) newTree = currentTree->getChild("_param", false);			                         
			if(!newTree) return currentTree->getChild("_na", true); //not available - must return a tree otherwise segfault       
			
			currentTree = newTree;         
		}                                                                         

		return currentTree;
	}
};

        

