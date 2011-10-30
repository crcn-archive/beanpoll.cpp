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
			pthread_mutex_init(&this->_pthreadMutex, NULL);         
		}; 
		
		ThreadTask* createTask(void* data,  ThreadCallback* callback );   
		
		bool canRemoveThread();
		
		friend class Thread;   
		
		
	private:
		std::list<Thread*> _threads;            
		std::list<Thread*> _waitingThreads;
		std::vector<Thread*> _closingThreads;
		std::vector<ThreadTask*> _waitingTasks;
		pthread_mutex_t _pthreadMutex;                   
		void removeThread(Thread*);
		
		void run(ThreadTask*);   
		void waiting(Thread*);
		ThreadTask* nextTask();    
		bool hasTask();
		                      
		
		
	   
	};
};

#endif