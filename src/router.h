#ifndef BEANPOLE_ROUTER_H_
#define BEANPOLE_ROUTER_H_   

#include "request.h"  
#include "data.h"      
#include "collection.h"     
#include 

namespace Beanpole
{   
	class ConcreteDispatcher
	{
	public:
		ConcreteDispatcher();
		
		void dispatch(Data* data); 
		void dispatch(Data* data, std::vector<RouteListener*> listeners);
		
	private:
		Collection _collection;	
	};  
	               
	
	class PullDispatcher 
	{
	public:
		
	};
	
	class PushDispatcher 
	{
		
	};
	
	class Router 
	{
		   
	public:
		                                                         
		/**
		 */
		
		void on(const char* route, void (*callback)(Beanpole::PullRequest*));     
		
		/**
		 */
		
		void on(const char* route, void (*callback)(Beanpole::PushRequest*));
	};
};

#endif