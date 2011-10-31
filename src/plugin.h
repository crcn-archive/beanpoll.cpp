#ifndef PLUGIN_H_
#define PLUGIN_H_
                         
#include <vector>   

namespace Beanpole
{
	class Router;
}    
    

typedef void (Bean)(Beanpole::Router*); 


namespace Beanpole
{ 
	
	void plugin(Bean* bean);   
	             
	std::vector<Bean*> beans;
};

#endif