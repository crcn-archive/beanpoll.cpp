CC := g++
OBJS :=  push_hello_world threads  

all: beanpole

%: %.cpp 
	@echo "Building $@"   
	$(CC) -I../src -c  $<
	$(CC)  $@.o -o $@
	chmod 755 $@  

beanpole: $(OBJS)
	@#echo "Building beanpole"
	@#@$(CC) $(OBJS) -o beanpole	

clean:
	@echo "Removing objects"
	@rm $(OBJS)

