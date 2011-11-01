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
		
		
		this->_waitingTasks.push(task);    
		
		
		//any waiting threads? use 'em
		if(this->_waitingWorkers.size())
		{                             
			//the last thread to finish will be the first to begin. Over time if there's less 
			//work to be done, we want threads to timeout - this does it. 
			thread = this->_waitingWorkers.back();               
			
			//remove the thread because it's being used.
			this->_waitingWorkers.pop_back();      
			
			
			this->_threadMutex.unlock();  
			thread->hasTask.signal();    
		}                                                 
		else 
			
			if(this->_workers.size() < this->maxWorkers)
			{     
				this->_threadMutex.unlock();           
				thread = new ThreadWorker(this, this->_workers.size());    
				this->_workers.push_back(thread);         
			}
		
		this->_threadMutex.unlock();  
		
		
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
		//std::cout << "RM" << std::endl;
		
		this->_threadMutex.lock();
		
		//remove from the running threads                  
		this->_workers.remove(thread);       
		
		//it should also be a waiting thread - need to remove it.    
		this->_waitingWorkers.remove(thread);
		
		delete thread;
		
	    this->_threadMutex.unlock();                      
	}
	
	
	ThreadTask* ThreadPool::nextTask()
	{   
		if(!this->hasTask()) return NULL;                                
		
		ThreadTask* task = this->_waitingTasks.front(); 
		this->_waitingTasks.pop();
		return task;
	}             
	
	bool ThreadPool::hasTask()
	{                
		return !!this->_waitingTasks.size();
	}
}

