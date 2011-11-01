#include "Beanpoll.cpp"   
#include <pthread.h>   
#include "timer.cpp"           

int start = 100000,
steps = start;    

void* sayHelloWorld(void* request)
{    
	if(!(--steps)) std::cout << "DONE" << std::endl;
	//usleep(500*1000);
}     


int main()
{                                   
	
	
	Beanpoll::ThreadBoss* pool = new Beanpoll::ThreadBoss();  
	
	int acc = 1;        
	
	double inc = 0;
	
	std::cout << "START" << std::endl;
	
	Timer timer;
	
	timer.start();
	
	for(int i = steps; i--;)    
	{                                                                          
		
		//run the new thread
		pool->createTask((void*)"hello world", &sayHelloWorld);  
		
		//std::cout << i << std::endl;
		//usleep(25*1000);
		
		
	}    
	
	timer.stop();
	
	printf("%d tasks in %d ms\n", start, timer.duration());
	
	
	int i;
	
	std::cin >> i;
	
	
}