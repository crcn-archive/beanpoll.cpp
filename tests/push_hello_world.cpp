#include "beanpole.h"           
                                                   
void sayHelloWorld(Beanpole::PushRequest* request)
{                                   
	std::cout << (const char*)request->data->getData() << std::endl;
}

int main()
{       
	Beanpole::Router* router = new Beanpole::Router();
	                                 
	router->on("push hello/world", &sayHelloWorld);
           
	                   
	for(int i = 100; i--;)                                         
	router->request("hello/world")->push((void*)"hello world!");      
	                               
	int i;
	
	std::cin >> i;
	                                                            
}