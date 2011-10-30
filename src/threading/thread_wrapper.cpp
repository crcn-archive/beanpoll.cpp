#include "thread_wrapper.h"    
#include <sys/time.h>   
#include <unistd.h>
                  



namespace Beanpole
{   
	void Thread::run(void* data)
	{
		pthread_create(&this->_thread, NULL, this->_callback, data);
	} 
	
	void* Thread::join()
	{
		void* result;
		
		pthread_join(this->_thread, &result);  
		
		return result;
	}                                         
	
	void Thread::detach()
	{
		pthread_detach(this->_thread);
	}    
	                               
	
	Thread::~Thread()
	{
		this->detach();
	}   
	
	
	ThreadMutex::ThreadMutex()
	{
		pthread_mutex_init(&this->_mutex, NULL);
	}                                     
	
	void ThreadMutex::lock()
	{
		pthread_mutex_lock(&this->_mutex);
	}                                     
	
	void ThreadMutex::unlock()
	{
		pthread_mutex_unlock(&this->_mutex);
	}                                       
	
	
	Thread::Thread(ThreadCallback* callback):
	_callback(callback)
	{                                                           
	}
	       
	
	ThreadCondition::ThreadCondition()
	{
		pthread_cond_init(&this->_condition, NULL);
	}                                             
	
	void ThreadCondition::wait(ThreadMutex& mutex)
	{
		pthread_cond_wait(&this->_condition, &mutex._mutex);
	}                                             
	
	void ThreadCondition::wait(ThreadMutex& mutex, int ttl)
	{                                      
		
		_ts.tv_sec  = _tp.tv_sec;
		_ts.tv_nsec = _tp.tv_usec * 1000;
	    _ts.tv_sec += ttl;         
		
		pthread_cond_timedwait(&this->_condition, &mutex._mutex, &_ts);
	}    
	
	void ThreadCondition::signal()
	{
		pthread_cond_signal(&this->_condition);
	}          
	
	void ThreadCondition::broadcast()
	{
		pthread_cond_broadcast(&this->_condition);
	}
	
	       
	
	
	
	
	
};