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
	
	class RouteTree 
	{        
	
	public: 
		
		/**
		 */
		
		std::string path;      
		
		/**
		 */
		
		std::vector<RouteListener*> listeners;
		
		
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
		                   
		
		std::map<std::string, RouteTree*> _children;
		
	};
	
	/**
	 */
	
	class Collection
	{
		
	public:  
		
		/**
		 */
		
		Collection(): _tree(new RouteTree("/")) { };
		
		/**
		 */
		
		void addRouteListener(RouteListener* listener);       
		
		/**
		 */
		
		void removeRouteListener(RouteListener* listener);
		
		/**
		 */
		
		std::vector<RouteListener*>& getRouteListeners(ChannelExpression* channel);     
		
	private:
		
		RouteTree* _tree;    
		                         
		RouteTree* getTree(ChannelExpression* channel, bool find);
	    RouteTree* getTree(ChannelExpression* channel)
		{
			return this->getTree(channel, false);
		}; 
	};
};


#endif