#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_       
                        
#include "thread.h"      
#include "thread_task.h"  
#include <iostream>
#include <list>  
#include <pthread.h>


namespace Beanpole
{
	class ThreadPool
	{
		
	public:   
		
		int maxThreads;
		int minThreads;
		
		ThreadPool(int maxThreads = 20, int minThreads = 2): 
		maxThreads(maxThreads), 
		minThreads(minThreads),
		_waitingThreads(0)
		{                                   
			// pthread_cond_init(&this->_hasTask, NULL);
			pthread_mutex_init(&this->_pthreadMutex, NULL);       
			
			struct sched_param param;
			                                            
			// pthread_attr_init(&this->_tattr);
			// std::cout <<pthread_attr_setschedpolicy(&this->_tattr, SCHED_FIFO);  
			// pthread_attr_setinheritsched(&this->_tattr, PTHREAD_EXPLICIT_SCHED);       
			// param.sched_priority = sched_get_priority_max(SCHED_FIFO);
			                                                  
			// pthread_attr_setschedparam(&this->_tattr, &param);
		}; 
		
		ThreadTask* createTask(void* data,  ThreadCallback* callback );   
		
		bool canRemoveThread();
		
		friend class Thread;   
		
		
	private:
		std::list<Thread*> _threads;            
		std::list<Thread*> _waitingThreads; 
		std::vector<ThreadTask*> _waitingTasks;
		pthread_mutex_t _pthreadMutex;  
		// pthread_attr_t _tattr;                      
		void removeThread(Thread*);
		
		void run(ThreadTask*);   
		void waiting(Thread*);
		ThreadTask* nextTask();    
		bool hasTask();
		                      
		
		
	   
	};
};

#endif