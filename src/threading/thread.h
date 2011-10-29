#ifndef THREAD_H_
#define THREAD_H_        

#include "thread_task.h"   
#include <pthread.h>

namespace Beanpole
{   
	class ThreadPool;   
	
	class Worker
	{
	public:
		Worker(Thread*);  
		
		void* run(ThreadTask* task);  
		
	private:
		Thread* _thread;
	};                  
	
	
	class Thread
	{
	public:  
		Thread(ThreadPool* pool);
                                         
		void run(ThreadTask* task);
		
		friend class ThreadTask;    

	private:
    	
		ThreadPool* _pool;
		ThreadTask* _currentTask;   
		pthread_t thread;
		           
		
		static void* execute(void*);   
		void done(void*); 
		
	};
};     


#endif