#ifndef EXPRESSIONS_H_
#define EXPRESSIONS_H_

#include <iostream>   
#include <tr1/unordered_map> 
#include <string>            
#include <map>     
#include <vector>
#include "tag.h"   

using namespace std::tr1;
      
namespace Beanpole
{   
	class PathExpression
	{       
	public:
		std::string value;
		bool param;     
		
		PathExpression(std::string value, bool param):
		value(value),
	    param(param) { };   
	
		PathExpression* clone();
	};
	                  
	
	class ChannelExpression
	{     
	public:
		std::string value;
		std::vector<PathExpression*> paths; 
		
		~ChannelExpression(); 
		
		ChannelExpression* clone();    
	};                 
	
	
	class ThruExpression
	{
	public:           
		ThruExpression* thru;
		ChannelExpression* channel;          
		
		ThruExpression(ChannelExpression* channel): channel(channel){ };
		ThruExpression(): channel(NULL){ };
		
		
	};                     
	
	
	class RouteExpression: public ThruExpression 
	{
	public:
		std::string type;        
		 
		RouteExpression(std::string type): 
		type(type)                                              
		{                                                                 
		};
		
		Beanpole::Tag* getTag(std::string name);    
		Beanpole::Tag* addTag(std::string name, Beanpole::Tag*); 
		bool hasTag(std::string name);                                           
		
	private:
		std::map<std::string, Beanpole::Tag*> _tags;
		
		
	};
};

#endif