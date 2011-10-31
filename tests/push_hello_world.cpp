#include "Beanpoll.cpp"  
// #include "timer.cpp"    

int steps = 0;     
// Timer tm;
                                                   
void sayHelloWorld(Beanpoll::PushRequest* request)
{                                                      
	// std::cout << (const char*)request->data->getData() << " " << steps++ << std::endl;    
	
	printf("%s %d\n", (const char*)request->read(), steps++);
	
	usleep(25*1000);
}

int main()
{       
	Beanpoll::Router* router = new Beanpoll::Router();
	                                               
	// for(int i = 2; i--;)
	router->on("push hello/world", &sayHelloWorld);
            

                                                 
                               
    while(1)
	{
		router->request("hello/world")->push((void*)"hello world!");          
		usleep(1000);
	}
	                                                
	int i;
	
	std::cin >> i;
	                                                            
}