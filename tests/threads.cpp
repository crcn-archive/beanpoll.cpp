#include "beanpole.cpp"   
#include <pthread.h>           

int steps;    
pthread_t thread; 
pthread_mutex_t mutex;
pthread_cond_t cond;
                                                   
void* sayHelloWorld(void* request)
{                                   
	std::cout << (const char*)request << " " << steps++ << std::endl;  
	
	//simulate busy thread, creating more threads - also variable.   
	usleep((rand() % 200 + 100)  * 1000);
	
	 
}     
    

int main()
{                                   
	                                                                            
	
	Beanpole::ThreadPool* pool = new Beanpole::ThreadPool(100, 2);  
	
	int acc = 1;        
	
	double inc = 0;
	                                
	                               
	while(1)    
	{                                                                          
		
		//run the new thread
		pool->createTask((void*)"hello world", &sayHelloWorld);  
		                                                
		                                                     
		//simulate variable activity. Testing creation & destruction of threads   
		int timeout = round(abs(sin(inc) * 50)) * 1000; 
		                                                      
		 
		//controls speed of sin func
		inc += 0.01;                    
		                                                                
		usleep(timeout);
	}    
	                                                   
                      
	                                                            
}