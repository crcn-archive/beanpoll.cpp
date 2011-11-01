#ifndef STREAM_H_
#define STREAM_H_

namespace Beanpoll
{
	class AbstractRequestStream
	{   
	public:                                                          
		
		virtual void* read() = 0;          
		
	private:
		void*(*_reader)(void*);   
		void* _data;
	};   
	
	class ConcreteRequestStream
	{   
	public:  
		ConcreteRequestStream(void*(*reader)(void*), void* data);    
		
	    void* read();          
		
	private:
		void*(*_reader)(void*);   
		void* _data;
	};
	
	class RequestStream : public ConcreteRequestStream
	{         
	public:                                          
		
		RequestStream():ConcreteRequestStream(&RequestStream::readData, NULL) {};
		RequestStream(void* data):ConcreteRequestStream(&RequestStream::readData, data) {};    
		
	private:  
		
		
		/**
		 */
		
		static void* readData(void* data)
		{
			return data;
		}
	};
};


#endif