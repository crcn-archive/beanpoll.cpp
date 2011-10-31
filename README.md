C++ version of Beanpoll

### Goals

- async request via multithreading. Similar to [Beanpoll.js](https://github.com/spiceapps/Beanpoll)  
-                                                                                              


### Example

    

````c++     

#include "Beanpoll.hpp"
                            
                                                   
void sayHelloWorld(Beanpoll::PushRequest* request)
{                                   
	std::cout << (const char*)request->data->getData() << std::endl;          
	                                  
	usleep(25*1000);
}

int main()
{       
	Beanpoll::Router* router = new Beanpoll::Router();
	               
	
	//async = multithreaded                  
	router->on("push -async hello/world", &sayHelloWorld);
                                                             

	for(int i = 1000; i--;) router->request("hello/world")->push((void*)"hello world!");      
	    
	
	//stop exist                                            
	int i;
	
	std::cin >> i;
	                                                            
}

    
````