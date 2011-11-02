

#ifneq ($(which clang++),"")
#	CC := clang++
#else
	CC := g++
	#OPTIONS := -O2 -ftree-vectorize -NDEBUG
	#OPTIONS := -Wl
#endif
       
SRC_DIR := src/
BUILD_DIR := build/
OBJS := beanpoll.o    
TESTS :=threads push_hello_world pull_hello_world plugin push_benchmark threads_benchmark

all: beanpoll tests

%.o: $(SRC_DIR)%.cpp
	@echo $(wildcard clang++) 
	@echo "Building $(BUILD_DIR)$@"     
	@$(CC) -c $< -o $(BUILD_DIR)$@   

beanpoll: $(OBJS)
	@echo "Building Beanpoll"
	@#$(CC) $(OBJS) -o Beanpoll	   

tests: $(TESTS)

%: tests/%.cpp
	@echo "Building test $@"  
	$(CC) -I$(SRC_DIR)  $(OPTIONS) -c  $< -o $(BUILD_DIR)$@.o
	@$(CC) $(BUILD_DIR)$@.o $(OPTIONS) -o $(BUILD_DIR)$@    
	@rm $(BUILD_DIR)$@.o 

  


clean:
	@echo "Removing objects"
	@rm $(BUILD_DIR)*.o  




