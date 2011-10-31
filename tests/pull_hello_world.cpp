#include "beanpole.cpp"       
                                
void onSayHello(Beanpole::PullRequest* request)
{   
	printf("%s\n", (const char*)request->data->getData());
	
	usleep(25*1000);
}    

void sayHello(Beanpole::PushRequest* request)
{
	std::cout << "RESPONSE!" << std::endl;
}

int main()
{       
	Beanpole::Router* router = new Beanpole::Router();
	                                 
	router->on("pull hello/world", &onSayHello);
            
                        
	router->request("hello/world")->pull((void*)"hello world", &sayHello);  
	
	int i = 0;
	
	std::cin >> i;
	                                                            
}