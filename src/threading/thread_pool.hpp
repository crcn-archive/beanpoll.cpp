#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_       
                       
#include "thread_worker.hpp"      
#include "thread_task.hpp"  
#include "thread_wrapper.hpp"
#include <iostream>
#include <list>  
#include <pthread.h>


namespace Beanpoll
{
	class ThreadPool
	{
		
	public:   
		                                  
		/**
		 * workers = threads
		 */
		
		int maxWorkers;     
		
		/**
		 * workers to keep allocated even if there are no tasks to be handled
		 */                                                                  
		
		int minWorkers;
		
		/**
		 */
		
		
		ThreadPool(int maxWorkers = 3, int minWorkers = 2);      
		/**
		 * creates a new task / job to run
		 */
		
		ThreadTask* createTask(void* data,  ThreadCallback* callback );                               
		
		
		/**
		 * returns TRUE if a worker can be removed. This runs up against minWorkers, and idling workers.
		 */
		
		
		bool canRemoveWorker();  
		
		/**
		 */
		
		static void* execute(void*);
		
		
		/**
		 * the thread worker needs access to some private methods in the thread pool, such as nextTask
		 */
		
		friend class ThreadWorker;   
		
		
	private:                 
		
	    /**
	     * All the workers registered in the pool including busy & waiting
	 	 */
	
		std::list<ThreadWorker*> _workers;                                
		
		/**
		 * workers waiting for tasks to come in. This will fill up if there's a delay between
		 * when tasks are added, and workers finish.
		 */
		
		std::list<ThreadWorker*> _waitingWorkers;   
		
		/**
		 * Queued up tasks waiting to be handled by workers. This gets filled if there are more
		 * jobs than there are workers to handle them
		 */
		
		std::vector<ThreadTask*> _waitingTasks;      
		           
		
		/**
		 * the locker which makes sure shared mem is accessed once between workers
		 */
		
		ThreadMutex _threadMutex;                                                
		
		
		/**
		 */
		
		ThreadMutex _poolMutex;
		
		/**
		 */
		
		ThreadCondition _taskCondition;
		
		/**
		 */
		
		Thread _poolThread;
		
		/**
		 * removes a given worker once it's been sitting around for too long
		 */
		
		void removeWorker(ThreadWorker*);                                   
		
		
		/**
		 * runs the given task, or throws the task in a queue if the workers
		 * are currently busy
		 */
		
		void run();
		
		/**
		 * notifies the pool that a worker is waiting for new tasks - this happens
		 * if there isn't stuff in the queue. 
		 */
		   
		void waiting(ThreadWorker*);          
		
		/**
		 * pops a task of the _waitingTasks queue, and returns it. This is called by the thread worker.
		 */
		
		ThreadTask* nextTask();   
		
		/**   
		 * returns TRUE if there are tasks in the tasks queue
		 */
		 
		bool hasTask();
		                      
		
		
	   
	};
};

#endif