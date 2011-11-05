#ifndef THREAD_TASK_H_
#define THREAD_TASK_H_  

#include "thread_callback.hpp"
#include "../linked_list.hpp"
#include "../garbage/object_pool.hpp"

namespace Beanpoll
{   
	class Thread;              
	
	class ThreadTask: public LinkedList<ThreadTask>
	{
	public:    
		
		/**
		 */
		
		void* _data;
		
		/**
		 */
		
		ThreadTask(void* data, ThreadCallback* callback): _data(data), _callback(callback){};    
		
		/**
		 */
		
		void* run(); 
		
		
		
		
		
		/**
		 */
		
		~ThreadTask();
		
	private:                                
		
		ThreadCallback* _callback;
	};
};      

#endif