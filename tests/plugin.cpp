#include "Beanpoll.cpp"   
#include <sched.h>  


void onHelloTest(Beanpoll::PushRequest* request)
{
	std::cout << "HELLO!" << std::endl;
}


void testPlugin(Beanpoll::Router* router)
{                                       
	router->on("push hello/test", &onHelloTest);
}

int main()
{       
	Beanpoll::Router* router = new Beanpoll::Router();                                                                
	Beanpoll::plugin(&testPlugin);      
	router->require(Beanpoll::beans);   
	
	
	router->request("hello/test")->push((void*)"hello/test");
	
	
	int i;
	
	std::cin >> i;
	
	
}