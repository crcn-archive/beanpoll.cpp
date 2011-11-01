#include "thread_task.hpp"


void* Beanpoll::ThreadTask::run()
{               
	return this->_callback(this->_data);
}               
