#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
                         
namespace Beanpole
{
	template<class T>
	class LinkedList
	{     
	public:      
		
		LinkedList():_nextSibling(NULL), _prevSibling(NULL) {};

		T* getNextSibling();
		void setNextSibling(T* sibling);  
		void addNextSibling(T* sibling);

		T* getPrevSibling();
		void setPrevSibling(T* sibling);
		void addPrevSibling(T* sibling);

		T* getLastSibling();
		void setLastSibling(T* sibling);

		T* getFirstSibling();
		void setFirstSibling(T* sibling); 
		
		T* remove(); 
		T* replace(T* list);
		

	private:

		T* _nextSibling;
		T* _prevSibling;
	};
};
              

#endif