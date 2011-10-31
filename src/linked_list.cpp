#include "linked_list.h"    

namespace Beanpole
{                          
	
	template<class T>
	T* LinkedList<T>::remove()
	{
		if(this->_prevSibling) this->_prevSibling->_nextSibling = this->_nextSibling;
		if(this->_nextSibling) this->_nextSibling->_prevSibling = this->_prevSibling;
		       
		//delete after remove...
		return (T*)this;
	}
	
	template<class T>
	T* LinkedList<T>::replace(T* list)
	{                                         
		list->_prevSibling = this->_prevSibling;
		list->_nextSibling = this->_nextSibling;   
		                                         
		if(this->_prevSibling) this->_prevSibling->_nextSibling = list;
		if(this->_nextSibling) this->_nextSibling->_prevSibling = list;
		
		return (T*)this;
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
		if(this->_nextSibling) this->_nextSibling->_prevSibling = sibling;
		this->_nextSibling = sibling;
	}
                       
	template<class T> 
	T* LinkedList<T>::getPrevSibling()
	{                                                      
		return this->_prevSibling;
	} 
	
	template<class T> 
	void LinkedList<T>::setPrevSibling(T* sibling)
	{
		if(this->_prevSibling) delete this->_prevSibling->replace(sibling);
	}
	
	template<class T> 
	void LinkedList<T>::addPrevSibling(T* sibling)
	{
		if(this->_prevSibling) this->_prevSibling->_nextSibling = sibling;
		this->_prevSibling = sibling;
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
		
		while(first->_prevSibling)
		{
			first = first->_prevSibling;
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