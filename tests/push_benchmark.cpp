#include "beanpoll.cpp"  
#include "timer.cpp" 
#include <sstream>

int start = 100000,
steps = start;      
Timer timer;

void onGetUsername(Beanpoll::PullRequest* request)
{
	Beanpoll::PushRequest* from = (Beanpoll::PushRequest*)(request->read());
	
	//std::cout << (const char*)from->read() << std::endl;
	
	
	request->end((void*)"username");
	from->end();
	
}

void getUsername(Beanpoll::RequestStream* stream)
{
	//Beanpoll::PullRequest* request = (Beanpoll::PullRequest*)(username->read());
	
	//std::cout << (const char*)stream->read() << std::endl;
	
	
}


void onSayHelloWorld(Beanpoll::PushRequest* request)
{       
	/*if(!atoi((char*)request->read()))
	{
		std::cout << "DONE" << std::endl;
		exit(0);
	}*/
	
	
	
	//request->router->request("username")->pull(request, &getUsername);
	
	request->end();
	
}

int main()
{       
	Beanpoll::Router* router = new Beanpoll::Router();
	
	router->on("push hello/world", &onSayHelloWorld);
	router->on("pull username", &onGetUsername);
	
	timer.start();
	
	
	
    for(int i = start; i--;)
	{
		router->request("hello/world")->push((void*)"hello craig");  
	}
	
	
	
	timer.stop();
	
	
	printf("%d tasks in %d ms\n", start, timer.duration());
	
	int i = 0;
	std::cin >> i;
	
}