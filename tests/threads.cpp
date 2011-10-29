#include "beanpole.cpp"              

int steps = 10;
                                                   
void* sayHelloWorld(void* request)
{                                   
	std::cout << (const char*)request << std::endl;     
	usleep(25*1000);
}

int main()
{       
	Beanpole::ThreadPool* pool = new Beanpole::ThreadPool(2);  
	                
	// for(int i = 100; i--;)
	pool->createTask((void*)"hello world", &sayHelloWorld); 
	                                      
	
while(1);
	
	                                                            
}