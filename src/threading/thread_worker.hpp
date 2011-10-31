#ifndef THREAD_H_
#define THREAD_H_        

#include "thread_task.hpp"   
#include "thread_wrapper.hpp"
#include <pthread.h>

namespace Beanpoll
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