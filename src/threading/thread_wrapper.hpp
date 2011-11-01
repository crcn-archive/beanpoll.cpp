#ifndef THREAD_WRAPPER_H_
#define THREAD_WRAPPER_H_    

#include <pthread.h>  
#include "thread_callback.hpp"

namespace Beanpoll
{   
	class Thread
	{   
	public:      
		
		Thread(){ };
		
		/**
		 */
		
		void run(void* data, ThreadCallback* callback);
		
		/**
		 * joins the result of the thread
		 */
		
		void* join();
		
		/**
		 * detaches the thread - cleans up resources
		 */
		
		void detach();    
		
		/**
		 * yields the current thread
		 */
		
		void yield();
		
		~Thread();
		
	private:
		pthread_t _thread; 
	};    
	
	class ThreadCondition;    
	
	
	class ThreadMutex
	{               
	public:      
		
		/**
		 */
		
		ThreadMutex();
		
		/**
		 */
		
		void lock();   
		
		/**
		 */
		
		void unlock();  
		
		friend class ThreadCondition;
		
	private:
		pthread_mutex_t _mutex;
	};
	
	
	
	
	class ThreadCondition
	{
	public:        
		
		ThreadCondition();
		
		/**
		 * wait until a condition has been broadcasted
		 */                                           
		
		void wait(ThreadMutex& mutex);
		
		
		/**
		 * wait for N seconds before continuing (kill timeout)
		 */
		
		void wait(ThreadMutex& mutex, int ttl);
		
		/**
		 * broadcasts to all waiting threads
		 */
		
		void broadcast();
		
		
		/**
		 * signals to one pthread, RR style
		 */
		
		void signal();                     
		
	private:
		pthread_cond_t _condition; 
		struct timespec _ts;
		struct timeval _tp;      
	};                     
	
	
};

#endif