#include "thread.h" 
#include "thread_pool.h"  
#include <sys/time.h>     


namespace Beanpole
{                    
	Thread::Thread(ThreadPool* pool, int index):
	_pool(pool),
	index(index)
	{                                    
		pthread_cond_init(&this->_hasTask, NULL);             
		
		//startup the thread                     
		pthread_create(&this->thread, NULL, &Thread::execute, (void*)this);
	}          
	 
	
	void Thread::waiting()
	{                              
		return this->_pool->waiting(this); 
	}                                            
	            
	           
	void* Thread::execute(void* t)
	{                                            
		Thread* thread = (Thread*)t;  
		ThreadTask* nextTask = NULL;
		                                     
		                
		struct timespec ts; 
	  	struct timeval  tp; 
	         
		//lovely magic numbers. TODO: put in constructor
		int tries = 0,
		waitTimeout = 1,
		sleepTimeout = 500 * 1000,
		maxTries = 1;
		
		bool killWait = false; 	
		                                                         
		
		while(1)
		{           
			tries = 0;    
			nextTask = NULL;
			          	  	                        
			
			pthread_mutex_lock(&thread->_pool->_pthreadMutex);       	                               

                                              
			
			//no more tasks? wait until there is one
			while(!killWait && !thread->_pool->hasTask())
			{               
				                 
				//notify the thread pool that a thread is waiting             
				thread->waiting(); 
				
				gettimeofday(&tp, NULL);    
				                     
				
				ts.tv_sec  = tp.tv_sec;
				ts.tv_nsec = tp.tv_usec * 1000;
			    ts.tv_sec += waitTimeout;           
			                                       
				             
				//either the thread pool signals *this* thread that there's a job, or it's killed. (Throttling N workers if idling)                                                              
				if(pthread_cond_timedwait(&thread->_hasTask, &thread->_pool->_pthreadMutex, &ts))
				{                                           
					//TODO - timeout here? need to enforce the timeout...
					// std::cout << "TIMEOUT" << std::endl;     
					// usleep()
				}                     
				                        
				
				if(!thread->_pool->canRemoveThread()) tries = 0;          
				// std::cout << tries << std::endl;
				
				killWait = ++tries > maxTries;                                                                                                                        
			}          
			              
			                                                            
			//if the thread was killed, we don't want it stealing from another thread.
			nextTask = killWait ? NULL : thread->_pool->nextTask();                                           
                               
                                                       

			pthread_mutex_unlock(&thread->_pool->_pthreadMutex);  
			         
			//does a task exist? means the condition was met - run it.
			if(nextTask)
			{                    
				std::cout << thread->index << std::endl;
				
				//run it.
				nextTask->run();
				delete nextTask;
			}                                              
			
			//otherwise, the condition timed out. Time to die.
			else         
			{                                      
				break;
			}              
		}  
		
		thread->_pool->removeThread(thread);          
	}
	
   
	
	/*void Thread::run(ThreadTask* task)
	{                        
		this->_currentTask = task;                                                   
		                 
		std::cout << "G" << std::endl;    
		                                                                    
	}*/  
	
	/*void Thread::done(void* response)
	{                           
		delete this->_currentTask;          
		this->_pool->done(this);  
		                          
		void* value;
		
		// pthread_join(this->thread,&value);    
		
	}*/
}