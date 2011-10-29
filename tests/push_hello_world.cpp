#include "beanpole.cpp"              

int steps = 10;
                                                   
void sayHelloWorld(Beanpole::PushRequest* request)
{                                   
	// std::cout << (const char*)request->data->getData() << std::endl;    
	if(!(--steps)) std::cout << "DONE" << std::endl;      
	
	std::cout << steps << std::endl;
	
	usleep(25*1000);
}

int main()
{       
	Beanpole::Router* router = new Beanpole::Router();
	                                 
	router->on("push -async hello/world", &sayHelloWorld);
                                                             

	// for(int i = steps; i--;)                                    
	router->request("hello/world")->push((void*)"hello world!");      
	                                                
	int i;
	
	std::cin >> i;
	                                                            
}