#ifndef THREAD_H_
#define THREAD_H_        

#include "thread_task.h"   
#include <pthread.h>

namespace Beanpole
{   
	class ThreadPool;    
	
	class Thread
	{
	public:  
		Thread(ThreadPool* pool, int index);        
		void run(ThreadTask* task);
		int index;     
		pthread_cond_t _hasTask;
		
		
		friend class ThreadTask;    

	private:
    	
		ThreadPool* _pool;
		ThreadTask* _currentTask;   
		pthread_t thread;          
		bool _waiting;        
		           
		
		static void* execute(void*);   
		void done(void*);   
		void waiting(); 
		
	};
};     


#endif