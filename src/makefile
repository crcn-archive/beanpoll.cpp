CC := g++
OBJS :=  beanpole.o  

all: beanpole

%.o: %.cpp
	@echo "Building $@"     
	@$(CC) -c $<   

beanpole: $(OBJS)
	@#echo "Building beanpole"
	@#$(CC) $(OBJS) -o beanpole	

clean:
	@echo "Removing objects"
	@rm *.o

