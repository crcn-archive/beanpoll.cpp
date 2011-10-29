C++ version of beanpole

### Goals

- async request via multithreading. Similar to (beanpole.js)[https://github.com/spiceapps/beanpole]  
-                                                                                              


### Example

    

````c++     

#include "beanpole.h"
                            
                                                   
void sayHelloWorld(Beanpole::PushRequest* request)
{                                   
	std::cout << (const char*)request->data->getData() << std::endl;          
	                                  
	usleep(25*1000);
}

int main()
{       
	Beanpole::Router* router = new Beanpole::Router();
	               
	
	//async = multithreaded                  
	router->on("push -async hello/world", &sayHelloWorld);
                                                             

	for(int i = 1000; i--;) router->request("hello/world")->push((void*)"hello world!");      
	    
	
	//stop exist                                            
	int i;
	
	std::cin >> i;
	                                                            
}

    
````