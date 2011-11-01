#include "Beanpoll.cpp"   
#include <pthread.h>   
#include "timer.cpp"      

int start = 100000,
steps = start;    


void* sayHelloWorld(void* request)
{    
	while(1);
}     


int main()
{                                   
	
	
	Beanpoll::ThreadBoss* pool = new Beanpoll::ThreadBoss();  
	
	int acc = 1;        
	
	double inc = 0;
	
	std::cout << "START" << std::endl;
	
	Timer timer;
	
	timer.start();
	
	pthread_t thread;
	
	int j = 0;
	
	for(int i = steps; i--;)    
	{                                                                          
		
		//sayHelloWorld(NULL);
		//run the new thread
		pool->createTask((void*)"hello world", &sayHelloWorld);  
		//std::cout << i << std::endl;
		//usleep(25*1000);
		
		
	}    
	
	timer.stop();
	
	printf("%d tasks in %d ms\n", start, timer.duration());
	
	
	//int i;
	
	//std::cin >> i;
	
	
}