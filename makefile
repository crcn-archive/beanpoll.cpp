

CC := g++          
SRC_DIR := src/
BUILD_DIR := build/
OBJS :=beanpoll.o      

all: beanpoll

%.o: $(SRC_DIR)%.cpp
	@echo "Building $(BUILD_DIR)$@"     
	@$(CC) -c $< -o $(BUILD_DIR)$@   

beanpoll: $(OBJS)
	@echo "Building Beanpoll"
	@#$(CC) $(OBJS) -o Beanpoll	  


clean:
	@echo "Removing objects"
	@rm $(BUILD_DIR)*.o

