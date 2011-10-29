CC := g++
OBJS := beanpole.o parser.o collection.o tag.o expressions.o listener.o router.o request.o data.o 

all: beanpole

%.o: %.cpp
	@echo "Building $@"
	@$(CC) -c $< 

beanpole: $(OBJS)
	@echo "Building beanpole"
	@$(CC) $(OBJS) -o beanpole	

clean:
	@echo "Removing objects"
	@rm *.o

