#ifndef MIDDLEWARE_H_
#define MIDDLEWARE_H_ 

#include "linked_list.h"
      
namespace Beanpole
{                   
	 
	class Middleware: public LinkedList<Middleware>
	{
	public:
		              
		
		/**
		 * moves to the next middleware item
		 */
		bool next();                        
		
		/**
		 * TRUE if there's sibling middleware
		 */
		
		bool hasNext();   
	};
};

#endif