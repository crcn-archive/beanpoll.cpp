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
		Thread* thread = NULL;        
		                                                                                
		
		pthread_mutex_lock(&this->_pthreadMutex);   
		
		this->_waitingTasks.push_back(task);    
		    
		                  
		//clean up any threads that might have been disposed of
		for(int i = this->_closingThreads.size(); i--;)
		{          
			thread = this->_closingThreads[i];    
			delete thread;
			
		}   
		this->_closingThreads.clear();
                                                                                     

		//any waiting threads? use 'em
		if(this->_waitingThreads.size())
		{                             
			//the last thread to finish will be the first to begin. Over time if there's less 
			//work to be done, we want threads to timeout - this does it. 
			thread = this->_waitingThreads.back();               
			
			//remove the thread because it's being used.
			this->_waitingThreads.pop_back();      
			                                            
			
			//signal the *target* thread.  
			pthread_cond_signal(&thread->_hasTask);        
		}                                                 
	    else 
		if(this->_threads.size() < this->maxThreads)
		{                                      
			thread = new Thread(this, this->_threads.size());    
			this->_threads.push_back(thread);            
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
		
		//remove from the running threads                  
		this->_threads.remove(thread);   
		
		//add for later cleanup. Needs to get to the main thread.
		this->_closingThreads.push_back(thread);                        
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

