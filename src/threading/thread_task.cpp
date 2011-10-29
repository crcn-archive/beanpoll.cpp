#include "thread_task.h"


void* Beanpole::ThreadTask::run()
{               
	return this->_callback(this->_data);
}               
                                                 