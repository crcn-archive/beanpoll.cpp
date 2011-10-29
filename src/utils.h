#ifndef UTILS_CPP_
#define UTILS_CPP_  

#include <iostream>      
#include <vector>    
#include <sstream>

namespace Beanpole
{
	std::string strToLowerCase(std::string s);    
	
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
                                                                                                                  
	std::vector<std::string> split(const std::string &s, char delim); 
	   
	template <class T> void deleteInVector(T* vect);
};                                           

#endif  

