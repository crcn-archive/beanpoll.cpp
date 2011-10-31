#include "linked_list.hpp"    

namespace Beanpoll
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
	    
};