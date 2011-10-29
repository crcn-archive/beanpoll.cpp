#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_       
                        
#include "thread.h"      
#include "thread_task.h"  
#include <iostream>
#include <list>


namespace Beanpole
{
	class ThreadPool
	{
		
	public:   
		
		int maxThreads;
		int minThreads;
		
		ThreadPool(int maxThreads = 20, int minThreads = 2): maxThreads(maxThreads), minThreads(minThreads){}; 
		
		ThreadTask* createTask(void* data,  ThreadCallback* callback ); 
		
		friend class Thread;   
		
		
	private:
		std::list<Thread*> _busyWorkers;
		std::list<Thread*> _waitingWorkers;
		std::list<ThreadTask*> _waitingTasks;    
		
		void run(ThreadTask*);      
		void done(Thread*);
		ThreadTask* popTask();
	   
	};
};

#endif