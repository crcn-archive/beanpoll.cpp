
#include <iostream>
#include <pthread.h>      
#include <vector>     
#include "callbacks.h"
#include "expressions.cpp"  
#include "router.cpp"     
#include "tag.cpp"
#include "utils.cpp"  
#include "listener.cpp" 
#include "collection.cpp"    
#include "parser.cpp"   
#include "request.cpp"
#include "data.cpp"

//parser.o collection.o tag.o expressions.o listener.o request.o  data.o router.o  

int jk = 10;


void *helloWorld(void* arg)
{                   
	jk++;
	
	std::cout << jk << std::endl;
	
	if(!arg)
	{
		std::cout << "FAIL" << std::endl;
		return NULL;
	}
	
	          
	while(1)
	{                   
		// std::cout << (const char*)arg << std::endl;

		usleep(100*1000);
	}                                                   
	return (void*)"GAH";
}


void test()
{
	//Beanpole::Collection col = Beanpole::Collection();
	//col.addRouteListener("push hello/world", helloWorld);
	//col.getRouteListeners()
}
              

void sayHelloWorld(Beanpole::PushRequest* request)
{
	std::cout << (const char*)request->data->getData() << std::endl;
}

void sayHelloWorld2(Beanpole::PushRequest* request)
{
	std::cout << (const char*)request->data->getData() << std::endl;
}


int main()
{
	pthread_t thread1;
	pthread_t thread2;
	                                     
    void *ret_join;
	
	std::vector<Beanpole::RouteExpression*> exprs;          
	
	Beanpole::Router* r = new Beanpole::Router();
	
	r->on("push hello/world", &sayHelloWorld);          
	
	r->request("hello/world")->push((void*)"hello world"); 
	/*                                        
	
	void onResult(PushRequest* request)
	{
	
	}
	  
	r->request("hello/world")->pull(onResult);                
	
	
	
	*/                
	                                                                
	
	
	int c;
	
	std::cin >> c;
	
	return 0;
	
	for(int i = 0; i < 10; i++)
	{
		pthread_create(&thread1, NULL, &helloWorld, (void*)"GAR"); 
	}
	
	//pthread_join(thread1, &ret_join);
	
	//std::cout << (const char*)ret_join << std::endl;
	
}
