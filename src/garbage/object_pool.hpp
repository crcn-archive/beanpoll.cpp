/*
 *  object_pool.h
 *  beanpoll
 *
 *  Created by Craig Condon on 11/4/11.
 *  Copyright 2011 Spice Apps LLC. All rights reserved.
 *
 */

#ifndef OBJECT_POOL_H_
#define OBJECT_POOL_H_

#include <queue>

namespace Beanpoll 
{
	template<class T>
	class ObjectPool
	{
	public:
		
		/**
		 * max number of objects
		 */
		
		int max;
		
		
		/**
		 * time to live per each object
		 */
		
		int ttl;
		
		/**
		 */
		
		ObjectPool(int max, int ttl):max(max), ttl(ttl) {
			
		};
		
		ObjectPool():max(50), ttl(-1) {
			
		}
		
		/**
		 */
		
		T* checkout();
		
		/**
		 */
		
		void checkin(T* object); 
		
	private:
		
		std::queue<T*> _pool;
	};
}

#endif


