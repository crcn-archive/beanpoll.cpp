#include "utils.hpp" 



namespace Beanpoll
{
	
	
	std::string strToLowerCase(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(),std::ptr_fun<int,int>(std::tolower));   
		
		return s;
	}    
	
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
	{
		std::stringstream ss(s);
		std::string item;
		while(std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}
	
	
	std::vector<std::string> split(const std::string &s, char delim) 
	{
		std::vector<std::string> elems;
		return split(s, delim, elems);
	} 
	
	template <class T> void deleteInVector(T* vect)
	{                                   
		for(int i = vect->size(); i--;)
		{
			delete (*vect)[i];
		}                                    
		
		vect->clear();
	}   
	
	template <class T> void cloneVector(T* vect, T* target)
	{                         
		for(int i = 0, n = vect->size(); i < n; i++)
		{        
			target->push_back((*vect)[i]->clone());
		}                                          
	}     
	
	
};   
