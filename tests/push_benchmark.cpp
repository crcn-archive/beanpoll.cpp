#include "Beanpoll.cpp"  
#include "timer.cpp" 
#include <sstream>

int start = 100000,
steps = start;      
Timer timer;

void sayHelloWorld(Beanpoll::PushRequest* request)
{       
	if(!atoi((char*)request->read()))
	{
		std::cout << "DONE" << std::endl;
		exit(0);
	}
	
	
	//std::cout << steps << std::endl;
	
	//usleep(1000);
}

int main()
{       
	Beanpoll::Router* router = new Beanpoll::Router();
	
	router->on("push hello/world", &sayHelloWorld);
	
	timer.start();
	
	
	
    for(int i = start; i--;)
	{
		char* buffer = new char[50];
		
		sprintf(buffer,"%d",i);
		
		//std::cout << (const char*)buffer << std::endl;
		
		router->request("hello/world")->push((void*)buffer);    
	}
	
	
	
	timer.stop();
	
	
	printf("%d tasks in %d ms\n", start, timer.duration());
	
	int i = 0;
	std::cin >> i;
	
}