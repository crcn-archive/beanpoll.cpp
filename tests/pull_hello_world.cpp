#include "beanpole.cpp"   
#include <sched.h>  


  
                                
void onSayHello(Beanpole::PullRequest* request)
{   
	printf("request: %s\n", (const char*)request->data->getData()); 
	                                                                  
	request->end((void*)"hello world!");     
}   



void sayHello(Beanpole::RequestStream* stream)
{                                   
	printf("response: %s\n", (const char*)stream->read());       
}

int main()
{       
	Beanpole::Router* router = new Beanpole::Router();
	                                 
	router->on("pull hello/world", &onSayHello);    
	                                     
                   
	for(int i = 100; i--;)     
	router->request("hello/world")->pull((void*)"hello world", &sayHello);  
	
	int i = 0;
	
	std::cin >> i;
	                                                            
}