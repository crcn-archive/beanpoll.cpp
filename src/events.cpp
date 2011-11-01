/*
 *  events.cpp
 *  beanpoll
 *
 *  Created by Craig Condon on 11/1/11.
 *  Copyright 2011 Spice Apps LLC. All rights reserved.
 *
 */

#include "events.hpp"


namespace Beanpoll
{
	template<class ListenerClass, class ResultClass>
	void EventListenerCollection<ListenerClass,ResultClass>::add(ListenerClass listener)
	{
		this->_listeners.push_back(listener);
	}
	
	template<class ListenerClass, class ResultClass>
	void EventListenerCollection<ListenerClass,ResultClass>::notify(ResultClass result)
	{
		
		//reverse makes it easier to remove if need be
		for(int i = this->_listeners.size(); i--;)
		{
			ListenerClass listener = this->_listeners[i];
			
			if(listener(result) == EVENT_LISTENER_REMOVE)
			{
				//this->_listeners.remove(i);
			}
		}
	}
};