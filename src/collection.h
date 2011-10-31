#ifndef BEANPOLE_COLLECTION_H_
#define BEANPOLE_COLLECTION_H_

#include <iostream>   
#include <vector> 
#include <map>              
#include "listener.h"  
#include "expressions.h"

/**
 */

namespace Beanpole
{    
	
	/**
	 */
	          
	template<class ListenerClass>
	class RouteTree 
	{        
	
	public: 
		
		/**
		 */
		
		std::string path;      
		
		/**
		 */
		
		std::vector<ListenerClass*> listeners;
		
		
		/**
		 */
		
		RouteTree(std::string path): path(path) {};           
		
		/**
		 */
		     
		
		RouteTree* getChild(std::string path, bool create = true)
		{   
			if(!this->_children[path] && create)
			{
				this->_children[path] = new RouteTree(path);
			}                                                             
			
			return this->_children[path];
		}
		
		
	private:
		                   
		
		std::map<std::string, RouteTree<ListenerClass>*> _children;
		
	};
	
	/**
	 */
	                    
	template<class ListenerClass>
	class Collection
	{
		
	public:  
		
		/**
		 */
		
		Collection(): _tree(new RouteTree<ListenerClass>("/")) { };
		
		/**
		 */
		
		void addRouteListener(ListenerClass* listener);       
		
		/**
		 */
		
		void removeRouteListener(ListenerClass* listener);
		
		/**
		 */
		
		std::vector<ListenerClass*>* getRouteListeners(ChannelExpression* channel);     
		
	private:
		
		RouteTree<ListenerClass>* _tree;    
		                         
		RouteTree<ListenerClass>* getTree(ChannelExpression* channel, bool find);
	    RouteTree<ListenerClass>* getTree(ChannelExpression* channel)
		{
			return this->getTree(channel, false);
		}; 
	};
};


#endif