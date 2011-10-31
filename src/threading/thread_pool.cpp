#include "thread_pool.h"
                  

namespace Beanpole
{        
	ThreadPool::ThreadPool(int maxWorkers, int minWorkers): 
	maxWorkers(maxWorkers), 
	minWorkers(minWorkers)
	{                                                            
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


		this->_threadMutex.lock();                        


		this->_waitingTasks.push_back(task);    


		//clean up any threads that might have been disposed of
		/*for(int i = this->_closingWorkers.size(); i--;)
		{                                       
			thread = this->_closingWorkers[i];   
			// delete thread;

		}   
		this->_closingWorkers.clear(); */


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
		else 
		if(this->_workers.size() < this->maxWorkers)
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
	
	void ThreadPool::removeWorker(ThreadWorker* thread)
	{                        	                   
		this->_threadMutex.lock();
		
		//remove from the running threads                  
		this->_workers.remove(thread);       
		
		//it should also be a waiting thread - need to remove it.    
		this->_waitingWorkers.remove(thread);
		
		//add for later cleanup. Needs to get to the main thread.
		// this->_closingWorkers.push_back(thread); 
		
		delete thread;
		                                            
	    this->_threadMutex.unlock();                      
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

