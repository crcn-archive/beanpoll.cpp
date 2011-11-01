#include "thread_worker.hpp" 
#include "thread_pool.hpp"    


namespace Beanpoll
{                    
	ThreadWorker::ThreadWorker(ThreadPool* pool, int index):
	_pool(pool),
	index(index)   
	{               
		this->_thread = new Thread();
		
		this->_thread->run((void*)this,&ThreadWorker::execute);      
		
	}         
	 
	
	void ThreadWorker::waiting()
	{                              
		return this->_pool->waiting(this); 
	}                                            
	            
	           
	void* ThreadWorker::execute(void* t)
	{                                            
		ThreadWorker* thread = (ThreadWorker*)t;  
		ThreadTask* nextTask = NULL;
		                          
	         
		//lovely magic numbers. TODO: put in constructor
		int tries = 0,
		waitTimeout = 1,
		sleepTimeout = 500 * 1000,
		maxTries = 2;
		
		bool killWait = false; 	
		                                                         
		
		while(1)
		{           
			tries = 0;    
			nextTask = NULL;
			          	  	                        
			       
			thread->_pool->_threadMutex.lock();                        	                               
                                                    
                                    
          
			
			//no more tasks? wait until there is one
			while(!killWait && !thread->_pool->hasTask())
			{               
				                 
				//notify the thread pool that a thread is waiting             
				thread->waiting();                   
				             
				 thread->hasTask.wait(thread->_pool->_threadMutex, waitTimeout);                     
				                        
				if(!thread->_pool->canRemoveWorker()) tries = 0;     
				
				killWait = ++tries > maxTries;                                                                                                                        
			}          
			              
			                                                            
			//if the thread was killed, we don't want it stealing from another thread.
			nextTask = killWait ? NULL : thread->_pool->nextTask();                                           
                                                     
                                                       
                                                                  
		    thread->_pool->_threadMutex.unlock();
			thread->_thread->yield();
			    
			
			//does a task exist? means the condition was met - run it.
			if(nextTask)
			{                             
				//run it.
				nextTask->run();
				delete nextTask;
			}                                              
			
			//otherwise, the condition timed out. Time to die.
			else
			if(killWait)
			{            
				break;
			}              
		}  
		
		thread->_pool->removeWorker(thread);   
		
		return NULL;
	}  
	           
	ThreadWorker::~ThreadWorker()
	{                                 
		delete this->_thread;
	}
	
          
}