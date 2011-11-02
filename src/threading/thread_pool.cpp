#include "thread_pool.hpp"


namespace Beanpoll
{        
	ThreadPool::ThreadPool(ThreadBoss* boss): 
	maxWorkers(3), 
	minWorkers(2),
	boss(boss),
	_nextTask(NULL)
	{                                                            
	};
	
	void ThreadPool::run(ThreadTask* task)
	{   
		
		
		ThreadWorker* thread = NULL;        
		
		
		this->_threadMutex.lock();                        
		
		if(!_nextTask)
		{
			_nextTask = task;
		}
		else 
		{
			_nextTask->getLastSibling()->addNextSibling(task);
		}
		

		
		//this->_waitingTasks.push(task);   
		
		
		//any waiting threads? use 'em
		if(this->_waitingWorkers.size())
		{                             
			//the last thread to finish will be the first to begin. Over time if there's less 
			//work to be done, we want threads to timeout - this does it. 
			thread = this->_waitingWorkers.back();               
			
			//remove the thread because it's being used.
			this->_waitingWorkers.pop_back();      
			
			
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
		this->_waitingWorkers.push_back(thread);
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
		
		ThreadTask* task = this->_nextTask;//this->_waitingTasks.front(); 
		//this->_waitingTasks.pop();
		this->_nextTask = this->_nextTask->getNextSibling();
		return task;
	}             
	
	bool ThreadPool::hasTask()
	{                
		return !!this->_nextTask;//!!this->_waitingTasks.size();
	}
}

