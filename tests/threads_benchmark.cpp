#include "Beanpoll.cpp"   
#include <pthread.h>   
#include "timer.cpp"           

int steps = 1000000;    

void* sayHelloWorld(void* request)
{    
	if(!(--steps)) std::cout << "DONE" << std::endl;
	usleep(500*1000);
}     


int main()
{                                   
	
	
	Beanpoll::ThreadPool* pool = new Beanpoll::ThreadPool(100, 2);  
	
	int acc = 1;        
	
	double inc = 0;
	
	
	Timer timer;
	
	timer.start();
	
	for(int i = steps; i--;)    
	{                                                                          
		
		//run the new thread
		pool->createTask((void*)"hello world", &sayHelloWorld);  
		
		//std::cout << i << std::endl;
		
		
	}    
	
	timer.stop();
	
	std::cout << "duration:" << timer.duration() << std::endl;
	
	
	int i;
	
	std::cin >> i;
	
	
}