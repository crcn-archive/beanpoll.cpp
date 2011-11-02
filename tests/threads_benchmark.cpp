#include "Beanpoll.cpp"   
#include <pthread.h>   
#include "timer.cpp"  
#include <deque>

int start = 100*100*100*10,
steps = start;    


void* sayHelloWorld(void* request)
{    
	//while(1);
}     




int main()
{          
	usleep(25*1000);
	
	
	//Beanpoll::ThreadBoss* pool = new Beanpoll::ThreadBoss();  
	
	int acc = 1;        
	
	double inc = 0;
	
	std::cout << "START" << std::endl;
	
	Timer timer;
	
	int k = 0;
	int diff = 10000;
	int s = diff;
	int yo = 1;
	
	while(1)
	{
		
		timer.start();
		
		//Beanpoll::LinkedQueue<Beanpoll::ThreadTask> queue;
		//std::vector<std::string*>* _tasks = new std::vector<std::string*>();
		
		int* b = new int[k];
		for(int i = k; i--;)    
		{     
			b[i] = i;
			//_tasks->push_back(new string("GGG"));
			
			//delete _tasks->back();
			//_tasks->pop_back();
			//Beanpoll::ThreadTask* tsk = new Beanpoll::ThreadTask(NULL,NULL);
			
			//queue.push(new Beanpoll::ThreadTask(NULL,NULL));
			//cue.push_front(i);
			
			//sayHelloWorld(NULL);
			//run the new thread
			//pool->createTask(NULL, &sayHelloWorld);  
			//std::cout << i << std::endl;
			
		} 
		
		k+=s;
		
		
		if(k == 0)
		{
			s = diff;
			break;
		}
		else if(k > start)
		{
			s = -diff;
		}
		
		/*for(int i = steps; i--;)
		{
			b[i] = 0;
			//delete b[i];
		}*/
		
		delete[] b;
		b = NULL;
		
		/*while(!queue.empty())
		{
			Beanpoll::ThreadTask* tk = queue.pop();
			delete tk;
		}*/
		
		/*while(_tasks->size())
		{
			delete _tasks->back();
			_tasks->pop_back();
		}*/
		
		//_tasks->clear();
		//delete _tasks;
		//_tasks = NULL;
		timer.stop();
		
		printf("%d tasks in %d ms \n", k, timer.duration());
		
	}
	  
	
	
	
	while(1)
	{
		std::cout << "DONE" << std::endl;
		usleep(100*1000);
	}
	
	
	
	/*while(1)
	{
		std::cout << "G" << std::endl;
		
		pool->createTask(NULL, &sayHelloWorld);  
		usleep(500*1000);
	}*/
	
	
	while(1)
	{
		usleep(100*1000);
	}
	
	int i;
	
	std::cin >> i;
	
	
}