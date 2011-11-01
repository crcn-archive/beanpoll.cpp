#include "Beanpoll.cpp"  
#include "timer.cpp"    

int steps = 1000;     
Timer timer;

void sayHelloWorld(Beanpoll::PushRequest* request)
{       
	if(!(--steps))
	{
		std::cout << "DONE" << std::endl;
	}
}

int main()
{       
	Beanpoll::Router* router = new Beanpoll::Router();
	
	router->on("push hello/world", &sayHelloWorld);
	
	timer.start();
	
	
	
    for(int i = steps; i--;)
	{
		router->request("hello/world")->push((void*)"hello world!");    
	}
	
	timer.stop();
	
	std::cout << "duration: " << timer.duration() << std::endl;
	
	int i;
	
	std::cin >> i;
	
}