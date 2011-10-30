#ifndef THREAD_TASK_H_
#define THREAD_TASK_H_  

#include "thread_callback.h"

namespace Beanpole
{   
	class Thread;              
	
	class ThreadTask
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