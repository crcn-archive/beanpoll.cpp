/*
 *  thread_boss
 *  beanpoll
 *
 *  Created by Craig Condon on 10/31/11.
 *  Copyright 2011 Spice Apps LLC. All rights reserved.
 *
 */

#include "thread_boss.hpp"
#include <sched.h>

namespace Beanpoll
{
	ThreadBoss::ThreadBoss()
	{
		this->_poolThread.run(this,&ThreadBoss::execute);
	}
	
	void ThreadBoss::createTask(void* data, ThreadCallback* callback)
	{
		ThreadTask* task = new ThreadTask(data, callback); 
		
		this->_poolMutex.lock();
		
		this->_tasks.push(task);

		this->_taskCondition.signal();
		this->_poolMutex.unlock();
	}
	
	void* ThreadBoss::execute(void* data)
	{
		ThreadBoss* boss = (ThreadBoss*)data;
		ThreadPool pool(boss);

		while(1)
		{
			boss->_poolMutex.lock();
			
			while(boss->_tasks.empty())
			{
				boss->_taskCondition.wait(boss->_poolMutex);
			}
			
			
			ThreadTask* task = boss->_tasks.shift();
			
			
			boss->_poolMutex.unlock();
			boss->_poolThread.yield();
			
			pool.run(task);
			
			
			
		}
		
		return NULL;
	}
}

