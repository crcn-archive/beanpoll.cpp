/*
 *  thread_boss
 *  beanpoll
 *
 *  Created by Craig Condon on 10/31/11.
 *  Copyright 2011 Spice Apps LLC. All rights reserved.
 *
 */

#include "thread_boss.hpp"

namespace Beanpoll
{
	ThreadBoss::ThreadBoss()
	{
		this->_poolThread.run(this,&ThreadBoss::execute);
	}
	
	ThreadTask* ThreadBoss::createTask(void* data, ThreadCallback* callback)
	{
		ThreadTask* task = new ThreadTask(data, callback); 
		
		//very slow.
		//this->_poolMutex.lock();
		_tasks.push(task);
		//this->_poolMutex.unlock();
		this->_taskCondition.signal();
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
			
			
			pool.run(boss->_tasks.front());
			
			boss->_tasks.pop();
			
			boss->_poolMutex.unlock();
		}
		
		return NULL;
	}
}

