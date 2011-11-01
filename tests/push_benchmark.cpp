#include "Beanpoll.cpp"  
#include "timer.cpp"    

int start = 100000,
steps = start;      
Timer timer;

void sayHelloWorld(Beanpoll::PushRequest* request)
{       
	if(!(--steps))
	{
		std::cout << "DONE" << std::endl;
	}
	
	usleep(1000);
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
	
	
	printf("%d tasks in %d ms\n", start, timer.duration());
	
	int i;
	
	std::cin >> i;
	
}