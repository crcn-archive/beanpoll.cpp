#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <vector>   

namespace Beanpoll
{
	class Router;
}    


typedef void (Bean)(Beanpoll::Router*); 


namespace Beanpoll
{           
	void plugin(Bean* bean);        
	std::vector<Bean*> beans;
};

#endif