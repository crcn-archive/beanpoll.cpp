#include "listener.h"          
#include "request.h"                


                                            
namespace Beanpole
{       
	
	        
	template<class RequestClass, class CallbackType>
	void RouteListener<RequestClass, CallbackType>::onRequest(RequestClass* request)
	{          
		this->_callback(request);
	}
};

