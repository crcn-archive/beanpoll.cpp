#include "thread_pool.hpp"


namespace Beanpoll
{        
	ThreadPool::ThreadPool(ThreadBoss* boss): 
	maxWorkers(100), 
	minWorkers(2),
	boss(boss)	
	{                                                            
	};
	
	void ThreadPool::run(ThreadTask* task)
	{   
		
		ThreadWorker* thread = NULL;        
		
		this->_threadMutex.lock();                        
		
		this->_tasks.push(task);

		
		//any waiting threads? use 'em
		if(!this->_waitingWorkers.empty())
		{                             
			//the last thread to finish will be the first to begin. Over time if there's less 
			//work to be done, we want threads to timeout - this does it. 
			thread = this->_waitingWorkers.pop();               
			
			thread->hasTask.signal();    
		}                                                 
		else if(this->_workers.size() < this->maxWorkers)
		{              
			thread = new ThreadWorker(this, this->_workers.size());    
			this->_workers.push_back(thread);         
		}
		
		this->_threadMutex.unlock();  
	}      
	
	void ThreadPool::waiting(ThreadWorker* thread)
	{                              	        
		this->_waitingWorkers.push(thread);
	} 
	
	bool ThreadPool::canRemoveWorker() 
	{
		return this->_workers.size() > this->minWorkers;
	}         
	
	void ThreadPool::removeWorker(ThreadWorker* worker)
	{            
		this->_threadMutex.lock();
		
		//remove from the running threads                  
		this->_workers.remove(worker);     
		
		//it should also be a waiting thread - need to remove it.    
		this->_waitingWorkers.remove(worker);
		
		delete worker;
		
	    this->_threadMutex.unlock();                      
	}
	
	
	ThreadTask* ThreadPool::nextTask()
	{   
		if(!this->hasTask()) return NULL;                                
		
		return this->_tasks.shift();
	}             
	
	bool ThreadPool::hasTask()
	{                
		return !this->_tasks.empty();
	}
}

