#ifndef THREAD_H_
#define THREAD_H_        

#include "thread_task.h"   
#include "thread_wrapper.h"
#include <pthread.h>

namespace Beanpole
{   
	class ThreadPool;    
	
	class ThreadWorker
	{
	public:         
		
		/**       
		 * the worker index in the pool. Helpful in debugging.
		 */    
		
		int index;      
		
		/**
		 */
		
		ThreadCondition hasTask;
		
		/**
		 */
		
		ThreadWorker(ThreadPool* pool, int index);        
		
		/**
		 */
		
		~ThreadWorker();                

	private:        
		
		/**
		 * the pool which owns this worker
		 */
		
		ThreadPool* _pool;    
		
		/**             
		 */            
		                             
		Thread* _thread;
		
		
		/**
		 * TRUE if the worker is waiting for more jobs/tasks
		 */
		          
		bool _waiting;        
		           
		                    
		/**
		 * threaded method 
		 */
		
		static void* execute(void*);     
		
		/**
		 * notifies the pool that the worker is waiting
		 */
		
		void waiting();                                
		
	};
};     


#endif