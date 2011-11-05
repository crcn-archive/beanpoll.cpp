#include "beanpoll.cpp"   
#include <pthread.h>   
#include <stdio.h>
#include "timer.cpp"  
#include <deque>

int start = 100*100*10,
steps = start;    


void* sayHelloWorld(void* request)
{    
	//while(1);
}     




int main()
{          
	usleep(25*1000);
	
	
	Beanpoll::ThreadBoss* pool = new Beanpoll::ThreadBoss();  
	
	Timer timer;
	
	std::cout << "START" << std::endl;
	
	timer.start();
	
	for (int i = steps; i--;) {
		
		pool->createTask(NULL, &sayHelloWorld);
	}
	
	timer.stop();
	
	printf("took %d ms to execute %d tasks\n", timer.duration(), start);
	
	int i;
	
	std::cin >> i;
	
	
}