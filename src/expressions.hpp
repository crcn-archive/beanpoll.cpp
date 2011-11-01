#ifndef EXPRESSIONS_H_
#define EXPRESSIONS_H_

#include <iostream>   
#include <string>            
#include <map>     
#include <vector>
#include "tag.hpp"   

      
namespace Beanpoll
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
		
		ThruExpression(ChannelExpression* channel): channel(channel), thru(NULL) { };
		ThruExpression(): channel(NULL), thru(NULL) { };
		
		
	};                     
	
	
	class RouteExpression: public ThruExpression 
	{
	public:
		std::string type;        
		 
		RouteExpression(std::string type): 
		type(type)                                              
		{                                                                 
		};
		
		Beanpoll::Tag* getTag(std::string name);    
		Beanpoll::Tag* addTag(std::string name, Beanpoll::Tag*); 
		bool hasTag(std::string name);                                           
		
	private:
		std::map<std::string, Beanpoll::Tag*> _tags;
		
		
	};
};

#endif