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
		                                                                                
		
		pthread_mutex_lock(&this->_pthreadMutex);   
		
		this->_waitingTasks.push_back(task);
                                                                                     

		//any waiting threads? use 'em
		if(this->_waitingThreads.size())
		{                             
			//the last thread to finish will be the first to begin. Over time if there's less 
			//work to be done, we want threads to timeout - this does it. 
			Thread* thread = this->_waitingThreads.back();               
			
			//remove the thread because it's being used.
			this->_waitingThreads.pop_back();      
			                                            
			
			//signal the *target* thread.  
			pthread_cond_signal(&thread->_hasTask);        
		}                                                 
	    else 
		if(this->_threads.size() < this->maxThreads)
		{                                      
			worker = new Thread(this, this->_threads.size());    
			this->_threads.push_back(worker);            
		}        
		
		pthread_mutex_unlock(&this->_pthreadMutex);

	}      
	
	void ThreadPool::waiting(Thread* thread)
	{                              	        
		this->_waitingThreads.push_back(thread);
	} 
	
	bool ThreadPool::canRemoveThread() 
	{
		return this->_threads.size() > this->minThreads;
	}         
	
	void ThreadPool::removeThread(Thread* thread)
	{                                      
		this->_threads.remove(thread);    
		delete thread;                                                  
	}
	   
	
	ThreadTask* ThreadPool::nextTask()
	{   
		if(!this->hasTask()) return NULL;                                
		
		ThreadTask* task = this->_waitingTasks.back(); 
		this->_waitingTasks.pop_back();
		return task;
	}             
	
	bool ThreadPool::hasTask()
	{                
		return !!this->_waitingTasks.size();
	}
}

