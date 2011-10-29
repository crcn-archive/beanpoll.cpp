CC := g++
OBJS :=  push_hello_world  

all: beanpole

%: %.cpp 
	@echo "Building $@"   
	$(CC) -I../src -c  $<
	$(CC) ../src/beanpole.o $@.o -o $@
	chmod 755 $@  

beanpole: $(OBJS)
	@#echo "Building beanpole"
	@#@$(CC) $(OBJS) -o beanpole	

clean:
	@echo "Removing objects"
	@rm $(OBJS)

