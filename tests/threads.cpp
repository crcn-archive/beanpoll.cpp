#include "beanpole.cpp"   
#include <pthread.h>           

int steps = 100 * 100 * 100 ;    
pthread_t thread; 
pthread_mutex_t mutex;
pthread_cond_t cond;
                                                   
void* sayHelloWorld(void* request)
{                                   
	std::cout << (const char*)request << " " << --steps << std::endl;     
	usleep(300 * 1000);
	
	 
}     
    

int main()
{                                   
	                                  
	// pthread_cond_init(&cond, NULL);		            
	// pthread_mutex_init(&mutex, NULL);                                      
	// pthread_create(&thread, NULL, &sayHelloWorld, (void*)"hello world!");
	// pthread_create(&thread, NULL, &sayHelloWorld, (void*)"hello world!");
	
	Beanpole::ThreadPool* pool = new Beanpole::ThreadPool(100, 2);  
	
	int acc = 1;        
	
	double inc = 0;
	                                
	                
	// for(int i = steps; i--;)
	while(1)    
	{                                   
		pool->createTask((void*)"hello world", &sayHelloWorld);  
		
		// std::cout << sin(inc) * 500 << std::endl;  
		                                                  
		int timeout = abs(sin(inc) * 500) * 1000; 
		                                         
		
		inc += 0.01;
		                                          
		usleep(timeout);
	}    
	                                                   
            
	int i;
	
	std::cin >> i;
	
	                                                            
}