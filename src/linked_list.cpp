#include "linked_list.hpp"    

namespace Beanpoll
{                          
	
	template<class T>
	T* LinkedList<T>::remove()
	{
		if(this->_prevSibling) this->_prevSibling->_nextSibling = this->_nextSibling;
		if(this->_nextSibling) this->_nextSibling->_prevSibling = this->_prevSibling;
		
		this->_nextSibling = NULL;
		this->_prevSibling = NULL;
		
		//delete after remove...
		return (T*)this;
	}
	
	template<class T>
	LinkedList<T>::~LinkedList()
	{
		this->remove();
	}
	
	
	template<class T>
	T* LinkedList<T>::getNextSibling()
	{
		return this->_nextSibling;
	} 
	
	
	template<class T> 
	void LinkedList<T>::addNextSibling(T* sibling)
	{
		if(this->_nextSibling) this->_nextSibling->_prevSibling = sibling;     
		sibling->_prevSibling = (T*)this;      
		sibling->_nextSibling = this->_nextSibling;  
		this->_nextSibling    = sibling;     
	}
	
	template<class T> 
	T* LinkedList<T>::getPrevSibling()
	{                                                      
		return this->_prevSibling;
	} 
	
	template<class T> 
	void LinkedList<T>::addPrevSibling(T* sibling)
	{
		if(this->_prevSibling) this->_prevSibling->_nextSibling = sibling;       
		sibling->_nextSibling = (T*)this;  
		sibling->_prevSibling = this->_prevSibling;
		this->_prevSibling    = sibling; 
		
	}
	
	template<class T> 
	T* LinkedList<T>::getLastSibling()
	{
		T* last = (T*)this;
		
		while(last->_nextSibling)
		{
			last = last->_nextSibling;
		} 
		
		return last; 
	}
	
	
	template<class T> 
	T* LinkedList<T>::getFirstSibling()
	{
		T* first = (T*)this;
		
		while(first->_prevSibling)
		{
			first = first->_prevSibling;
		}                                   
		
		return first;
	}
	
	
	
	template<class T>
	void LinkedQueue<T>::push(T* item)
	{
		
		if(!this->_next)
		{
			this->_next = item;
		}
		else 
		{
			_last->addNextSibling(item);
		}
		
		this->_size++;
		_last = item;
	}
	
	template<class T>
	void LinkedQueue<T>::unshift(T* item)
	{
		if(!this->_next)
		{
			this->_next = item;
		}
		else 
		{
			T* oldNext = this->_next;
			this->_next = item;
			this->_next->addNextSibling(oldNext);
		}
		
		this->_size++;
	}
	
	template<class T>
	T* LinkedQueue<T>::pop()
	{
		
		if(!this->_last) return NULL;
		
		this->_size--;
		T* current = this->_last;
		this->_last = current->getPrevSibling();
		current->remove();
		
		if(!this->_last) this->_next = NULL;
		
		return current;
	}
	
	template<class T>
	T* LinkedQueue<T>::shift()
	{
		if(!this->_next) return NULL;
			
		this->_size--;
		T* current = this->_next;
		this->_next = current->getNextSibling();
		current->remove();
		
		
		if(!this->_next) this->_last = NULL;
		
		return current;
	}
	
	template<class T>
	void LinkedQueue<T>::remove(T* item)
	{
		T* current = this->_next;
		
		while(current != NULL && current != item)
		{
			current = current->getNextSibling();
		}
		
		if(current) current->remove();
		
	}
	
	template<class T>
	bool LinkedQueue<T>::empty()
	{
		return this->_next == NULL;
	}
	
	template<class T>
	int LinkedQueue<T>::size()
	{
		return this->_size;
	}
	
};