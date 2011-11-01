/*
 *  thread_boss.h
 *  beanpoll
 *
 *  Created by Craig Condon on 10/31/11.
 *  Copyright 2011 Spice Apps LLC. All rights reserved.
 *
 */

#ifndef THREAD_BOSS_H_
#define THREAD_BOSS_H_

#include "thread_pool.hpp"
#include <queue>

namespace Beanpoll 
{
	class ThreadBoss
	{
	public:
		ThreadBoss();
		ThreadTask* createTask(void* data,  ThreadCallback* callback);
		
		friend class ThreadPool;
		
		
	private:
		
		Thread _poolThread;
		ThreadMutex _poolMutex;
		ThreadCondition _taskCondition;
		std::queue<ThreadTask*> _tasks;
		
		static void* execute(void*);
	};
};

#endif