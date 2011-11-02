#include "Beanpoll.cpp"   
#include <pthread.h>   
#include "timer.cpp"  
#include <deque>

int start = 10000,
steps = start;    


void* sayHelloWorld(void* request)
{    
	//while(1);
}     


int main()
{          
	usleep(25*1000);
	
	
	Beanpoll::ThreadBoss* pool = new Beanpoll::ThreadBoss();  
	
	int acc = 1;        
	
	double inc = 0;
	
	std::cout << "START" << std::endl;
	
	Timer timer;
	
	timer.start();
	
	pthread_t thread;
	
	int j = 0;
	
	std::deque<int> cue;
	
	for(int i = steps; i--;)    
	{                   
		//cue.push_front(i);
		
		//sayHelloWorld(NULL);
		//run the new thread
		pool->createTask(NULL, &sayHelloWorld);  
		//std::cout << i << std::endl;
		
		
	}   
	
	/*while(cue.size())
	{
		cue.pop_back();
	}
	
	cue.clear();
	cue.resize(0);*/
	std::cout << cue.size() << std::endl;
	//cue.resize(0);
	//std::cout << cue.capacity() << std::endl;
	
	
	
	
	timer.stop();
	
	printf("%d tasks in %d ms\n", start, timer.duration());
	
	
	
	/*while(1)
	{
		std::cout << "G" << std::endl;
		
		pool->createTask(NULL, &sayHelloWorld);  
		usleep(500*1000);
	}*/
	
	
	int i;
	
	std::cin >> i;
	
	
}