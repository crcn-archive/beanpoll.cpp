CC := g++
OBJS :=  push_hello_world pull_hello_world plugin threads  

all: Beanpoll

%: %.cpp 
	@echo "Building $@"   
	$(CC) -I../src -c  $<
	$(CC)  $@.o -o $@
	chmod 755 $@  

Beanpoll: $(OBJS)
	@#echo "Building Beanpoll"
	@#@$(CC) $(OBJS) -o Beanpoll	

clean:
	@echo "Removing objects"
	@rm $(OBJS)

