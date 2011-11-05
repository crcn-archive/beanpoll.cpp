/*
 *  object_pool.cpp
 *  beanpoll
 *
 *  Created by Craig Condon on 11/4/11.
 *  Copyright 2011 Spice Apps LLC. All rights reserved.
 *
 */

#include "object_pool.hpp"


namespace Beanpoll 
{
	template<class T>
	T* ObjectPool<T>::checkout()
	{
		if(this->_pool.empty()) return new T();
		
		T* object = this->_pool.front();
		this->_pool.pop();
		return object;
	}
	
	template<class T>
	void ObjectPool<T>::checkin(T* object)
	{
		if(this->_pool.size() > this->max)
		{
			delete object;
			return;
		}
		
		this->_pool.push(object);
	}
}

