#include "beanpole.cpp"  
// #include "timer.cpp"    

int steps = 0;     
// Timer tm;
                                                   
void sayHelloWorld(Beanpole::PushRequest* request)
{                                                      
	// std::cout << (const char*)request->data->getData() << " " << steps++ << std::endl;    
	
	printf("%s %d\n", (const char*)request->data->getData(), steps++);
	
	usleep(25*1000);
}

int main()
{       
	Beanpole::Router* router = new Beanpole::Router();
	                                               
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