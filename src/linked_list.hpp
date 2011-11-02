#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

namespace Beanpoll
{
	template<class T>
	class LinkedList
	{     
	public:      
		
		LinkedList():_nextSibling(NULL), _prevSibling(NULL) {};
		
		T* getNextSibling();                  
		void addNextSibling(T* sibling);
		
		T* getPrevSibling();                
		void addPrevSibling(T* sibling);
		
		T* getLastSibling();  
		T* getFirstSibling();                 
		
		T* remove(); 
		T* replace(T* list);
		
		~LinkedList();
		
		
	private:
		
		T* _nextSibling;
		T* _prevSibling;
	};
	
	
	template<class T>
	class LinkedQueue
	{
	public:
		
		/**
		 */
		LinkedQueue():
		_next(NULL),
		_last(NULL) 
		{
		};
		
		/**
		 */
		
		void unshift(T* item);
		
		/**
		 */
		
		void push(T* item);
		
		/**
		 */
		
		T* pop();
		
		/**
		 */
		
		T* shift();
		
		/**
		 */
		
		void remove(T* item);
		
		/**
		 */
		
		bool empty();
		
		/**
		 */
		
		int size();
		
	private:
		
		T* _next;
		T* _last;
		int _size;
	};
};


#endif