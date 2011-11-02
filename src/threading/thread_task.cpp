#include "thread_task.hpp"


namespace Beanpoll 
{
	void* ThreadTask::run()
	{               
		return this->_callback(this->_data);
	}
	
	ThreadTask::~ThreadTask()
	{        
	}
}
               

