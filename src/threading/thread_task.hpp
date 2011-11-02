#ifndef THREAD_TASK_H_
#define THREAD_TASK_H_  

#include "thread_callback.hpp"
#include "linked_list.hpp"

namespace Beanpoll
{   
	class Thread;              
	
	class ThreadTask: public LinkedList<ThreadTask>
	{
	public:         
		
		ThreadTask(void* data, ThreadCallback* callback): _data(data), _callback(callback){};    
		
		void* run();    
		
	private:                                
		
		ThreadCallback* _callback;
		void* _data;
		
	};
};      

#endif