#include "Beanpoll.cpp"   
#include <sched.h>  


  
                                
void onSayHello(Beanpoll::PullRequest* request)
{   
	printf("request: %s\n", (const char*)request->read());  
	
	//request->end((void*)request->getParam("name"));
	                                                                  
	request->end((void*)"hello world!");     
}        

void onAuth2(Beanpoll::PullRequest* request)
{
	std::cout << "trefdsfa" << std::endl;
	                   
	usleep(200*1000);
	request->next();  
	                    
}  

void onAuth(Beanpoll::PullRequest* request)
{
	std::cout << "authenticating..." << std::endl;                
	                       
	usleep(200*1000);  
	                        
	
	if(request->next())
	{
		std::cout << "nexted!" << std::endl;
	}
}



void sayHello(Beanpoll::RequestStream* stream)
{                                   
	printf("response: %s\n", (const char*)stream->read());       
}

int main()
{       
	Beanpoll::Router* router = new Beanpoll::Router();
	
	router->on("pull auth2", &onAuth2);
	router->on("pull auth", &onAuth);                                 
	router->on("pull auth2 -> auth2 -> auth -> auth -> auth -> auth -> hello/:name", &onSayHello);    
	                                     
                   
	// for(int i = 100; i--;) 
	while(1)
	{    
		router->request("hello/craig")->pull((void*)"hello world", &sayHello);  
		usleep(25*1000);
	}
	
	int i = 0;
	
	std::cin >> i;
	                                                            
}