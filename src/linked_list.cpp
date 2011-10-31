#include "linked_list.h"    

namespace Beanpole
{                          
	
	template<class T>
	T* LinkedList<T>::remove()
	{
		if(this->_previousSibling) this->_previousSibling->_nextSibling = this->_nextSibling;
		if(this->_nextSibling) this->_nextSibling->_previousSibling = this->_previousSibling;
		       
		//delete after remove...
		return (T*)this;
	}
	
	template<class T>
	T* LinkedList<T>::replace(T* list)
	{                                         
		list->_previousSibling = this->_prevousSibling;
		list->_nextSibling = this->_nextSibling;   
		                                         
		if(this->_previousSibling) this->_previousSibling->_nextSibling = list;
		if(this->_nextSibling) this->_nextSibling->_previousSibling = list;
		
		return this;
	}   
	
	template<class T>
	T* LinkedList<T>::getNextSibling()
	{
		return this->_nextSibling;
	} 
	
	template<class T> 
	void LinkedList<T>::setNextSibling(T* sibling)
	{
		if(this->_nextSibling) delete this->_nextSibling->replace(sibling);      
	}  
	
	template<class T> 
	void LinkedList<T>::addNextSibling(T* sibling)
	{
		if(this->_nextSibling) this->_nextSibling->_previousSibling = sibling;
		this->_nextSibling = sibling;
	}
                       
	template<class T> 
	T* LinkedList<T>::getPreviousSibling()
	{                                                      
		return this->_previousSibling;
	} 
	
	template<class T> 
	void LinkedList<T>::setPreviousSibling(T* sibling)
	{
		if(this->_previousSibling) delete this->_previousSibling->replace(sibling);
	}
	
	template<class T> 
	void LinkedList<T>::addPreviousSibling(T* sibling)
	{
		if(this->_previousSibling) this->_previousSibling->_nextSibling = sibling;
		this->_previousSibling = sibling;
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
	void LinkedList<T>::setLastSibling(T* sibling)
	{
		T* last = this->getLastSibling();
		           
		//hmm - what if it's itself?
		delete last->replace(sibling);
	}
                      
	template<class T> 
	T* LinkedList<T>::getFirstSibling()
	{
		T* first = (T*)this;
		
		while(first->_previousSibling)
		{
			first = first->_previousSibling;
		}                                   
		
		return first;
	}
	
	template<class T> 
	void LinkedList<T>::setFirstSibling(T* sibling)
	{
		T* first = this->getFirstSibling();
		
		delete first->replace(sibling);
	}
};