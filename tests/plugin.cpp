#include "beanpole.cpp"   
#include <sched.h>  

             
void onHelloTest(Beanpole::PushRequest* request)
{
	std::cout << "HELLO!" << std::endl;
}
  
                                
void testPlugin(Beanpole::Router* router)
{                                       
	router->on("push hello/test", &onHelloTest);
}

int main()
{       
	Beanpole::Router* router = new Beanpole::Router();                                                                
	Beanpole::plugin(&testPlugin);      
	router->require(Beanpole::beans);   
	
	
	router->request("hello/test")->push((void*)"hello/test");
	      
	
	int i;
	
	std::cin >> i;
	           
	                                                            
}