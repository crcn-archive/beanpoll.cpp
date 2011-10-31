#include "beanpole.cpp"   
#include <sched.h>  


  
                                
void onSayHello(Beanpole::PullRequest* request)
{   
	printf("request: %s\n", (const char*)request->read()); 
	                                                                  
	request->end((void*)"hello world!");     
}          

void onAuth(Beanpole::PullRequest* request)
{
	std::cout << "authenticating..." << std::endl;                
	                 
	//hit the database
	usleep(200*1000);  
	              
	request->end((void*)"unauthorized.");       
	
	return;
	
	if(request->next())
	{
		std::cout << "nexted!" << std::endl;
	}
}



void sayHello(Beanpole::RequestStream* stream)
{                                   
	printf("response: %s\n", (const char*)stream->read());       
}

int main()
{       
	Beanpole::Router* router = new Beanpole::Router();
	
	router->on("pull auth", &onAuth);                                 
	router->on("pull auth -> hello/:name", &onSayHello);    
	                                     
                   
	// for(int i = 100; i--;) 
	{    
		router->request("hello/craig")->pull((void*)"hello world", &sayHello);  
		// usleep(25*1000);
	}
	
	int i = 0;
	
	std::cin >> i;
	                                                            
}