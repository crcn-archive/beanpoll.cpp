#include "thread.h" 
#include "thread_pool.h"       


namespace Beanpole
{   
	Worker::Worker(Thread* thread):
	_thread(thread)
	{              
	}   
	
	void* Worker::run(ThreadTask* task)
	{             
		
		// return this->_thread->done(task->run());
	}           
	
	
	Thread::Thread(ThreadPool* pool):
	_pool(pool)
	{                                                                 
		pthread_create(&this->thread, NULL, &Thread::execute, (void*)this);
	}                 
	
	           
	void* Thread::execute(void* t)
	{                    
		// ((Thread*)t)->worker = new Worker((Thread*)t);
		
		std::cout << "RUN" << std::endl;          
		
		while(1);
	}
	
   
	
	void Thread::run(ThreadTask* task)
	{                        
		this->_currentTask = task;                                                   
		                 
		std::cout << "G" << std::endl;    
		                                                                    
	}  
	
	void Thread::done(void* response)
	{                           
		delete this->_currentTask;          
		this->_pool->done(this);  
		                          
		void* value;
		
		// pthread_join(this->thread,&value);    
		
	}
}