#include "thread_pool.h"
                  

namespace Beanpole
{        
	ThreadPool::ThreadPool(int maxWorkers, int minWorkers): 
	maxWorkers(maxWorkers), 
	minWorkers(minWorkers),
	_waitingWorkers(0)
	{                                                
		pthread_mutex_init(&this->_pthreadMutex, NULL);         
	};
	        
                            
	ThreadTask* ThreadPool::createTask(void* data,  ThreadCallback* callback )
	{
		ThreadTask* task = new ThreadTask(data, callback);  
		                  
		this->run(task);
		
		return task;
	}; 
	
	
	void ThreadPool::run(ThreadTask* task)
	{   
		ThreadWorker* thread = NULL;        
		                                                                                
		
		pthread_mutex_lock(&this->_pthreadMutex);
		                                     
		
		this->_waitingTasks.push_back(task);    
		    
		                  
		//clean up any threads that might have been disposed of
		for(int i = this->_closingWorkers.size(); i--;)
		{          
			thread = this->_closingWorkers[i];   
			delete thread;
			
		}   
		this->_closingWorkers.clear();
                                                                                     

		//any waiting threads? use 'em
		if(this->_waitingWorkers.size())
		{                             
			//the last thread to finish will be the first to begin. Over time if there's less 
			//work to be done, we want threads to timeout - this does it. 
			thread = this->_waitingWorkers.back();               
			
			//remove the thread because it's being used.
			this->_waitingWorkers.pop_back();      
			                                            
			
			//signal the *target* thread.  
			pthread_cond_signal(&thread->_hasTask);        
		}                                                 
	    else 
		if(this->_workers.size() < this->maxWorkers)
		{                                      
			thread = new ThreadWorker(this, this->_workers.size());    
			this->_workers.push_back(thread);            
		}        
		
		pthread_mutex_unlock(&this->_pthreadMutex);

	}      
	
	void ThreadPool::waiting(ThreadWorker* thread)
	{                              	        
		this->_waitingWorkers.push_back(thread);
	} 
	
	bool ThreadPool::canRemoveWorker() 
	{
		return this->_workers.size() > this->minWorkers;
	}         
	
	void ThreadPool::removeWorker(ThreadWorker* thread)
	{                        	
		pthread_mutex_lock(&this->_pthreadMutex);
		
		//remove from the running threads                  
		this->_workers.remove(thread);       
		
		//it should also be a waiting thread - need to remove it.    
		this->_waitingWorkers.remove(thread);
		
		//add for later cleanup. Needs to get to the main thread.
		this->_closingWorkers.push_back(thread); 
		
		pthread_mutex_unlock(&this->_pthreadMutex);                       
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

