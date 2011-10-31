#ifndef TAG_H_
#define TAG_H_

#include <iostream>
      
namespace Beanpole
{         
	class Tag
	{
	public:

		virtual void* value() = 0;
	};              


	class StringTag: public Tag
	{   
	private:
		std::string _value;

	public:          

		StringTag(std::string value):_value(value) { };  
		StringTag(const char* value):_value(value) { };
		StringTag():_value("") { };

		void* value();
	};                    


	class NumberTag: public Tag
	{
	public:
		void* value();
	};
	
	class BooleanTag: public Tag
	{              
	private:
		bool _value;
		
	public:         
		
		BooleanTag(bool value): _value() { };
		
		void* value();
	};


};

#endif