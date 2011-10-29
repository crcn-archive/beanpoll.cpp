#include "thread_pool.h"
                  

namespace Beanpole
{
	        
                            
	ThreadTask* ThreadPool::createTask(void* data,  ThreadCallback* callback )
	{
		ThreadTask* task = new ThreadTask(data, callback);      
		
		this->run(task);
		
		return task;
	}; 
	
	
	void ThreadPool::run(ThreadTask* task)
	{   
		Thread* worker = NULL;    
		                                    
		          
		
		//any waiting threads?
		if(this->_waitingWorkers.size())
		{          
			worker = this->_waitingWorkers.back();
			this->_waitingWorkers.pop_back();           
		}                                
		                          
		
		//can we still add threads?
		else
		if(this->_busyWorkers.size() < this->maxThreads)
		{                          
			worker = new Thread(this);                
		}                                
		
		if(worker)
		{
			this->_busyWorkers.push_back(worker);
			worker->run(task);
		}                                
		else
		{
			this->_waitingTasks.push_back(task);
		}
		
		
	} 
	
	void ThreadPool::done(Thread* thread)
	{                       
		
		//once a thread is done, pop the next task off
		ThreadTask* task = this->popTask();
		                                              
		//*if* there's a thread, then it's still busy - run it.
		if(task)
		{          
			thread->run(task);
			return;
		}         
		            
		                                      
		//otherwise we need to wait
		this->_waitingWorkers.push_back(thread);
	}   
	
	ThreadTask* ThreadPool::popTask()
	{   
		if(!this->_waitingTasks.size()) return NULL;                                
		
		ThreadTask* task = this->_waitingTasks.back(); 
		this->_waitingTasks.pop_back();
		return task;
	}
}

