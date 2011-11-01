/*
 *  events.h
 *  beanpoll
 *
 *  Created by Craig Condon on 11/1/11.
 *  Copyright 2011 Spice Apps LLC. All rights reserved.
 *
 */



#ifndef EVENTS_H_
#define EVENTS_H_

#include <list>

#define EVENT_LISTENER_KEEP 0
#define EVENT_LISTENER_REMOVE 1

namespace Beanpoll 
{
	template<class ListenerClass, class ResultClass>
	class EventListenerCollection
	{
	public:
		
		/**
		 * adds a listener to the particular event
		 */
		
		void add(ListenerClass listener);
		
		/**
		 * notifies all the listeners in the collection
		 */
		
		void notify(ResultClass result);
		
		
	private:
		std::vector<ListenerClass> _listeners;
	};
}

#endif