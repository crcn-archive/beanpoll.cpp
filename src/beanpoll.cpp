//yeah, ugly as shit, but fixes an issue with g++ where templates aren't found...
                

#include <iostream>
#include <pthread.h>      
#include <vector>     
#include "callbacks.hpp"
#include "expressions.cpp"  
#include "router.cpp"     
#include "tag.cpp"
#include "utils.cpp"  
#include "listener.cpp" 
#include "collection.cpp"    
#include "parser.cpp"   
#include "request.cpp"
#include "message.cpp"             
#include "stream.cpp"
#include "middleware.cpp"  
#include "linked_list.cpp"       
#include "plugin.cpp"
#include "events.cpp"
#include "garbage/object_pool.cpp"
#include "threading/thread_task.cpp"
#include "threading/thread_worker.cpp" 
#include "threading/thread_wrapper.cpp"       
#include "threading/thread_pool.cpp"    
#include "threading/thread_boss.cpp"



