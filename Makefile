CXX 	 		:= g++
CXXFLAGS 	:= -std=c++14 -Wall 

LIB_DIR    	:= -L boost_1_61_0/libs -L lib/opencv/build/lib/
LIBRARIES   := -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lrt -lpthread
LIB_INC 		:= -I boost_1_61_0/ -I lib/opencv/build/include/

BIN_DIR    	:= bin
INC_DIR    	:= -I include
INC_DIR    	+= $(LIB_INC)
SRC_DIR    	:= src
EXECUTABLE  := Application

all:  $(BIN_DIR)/$(EXECUTABLE)

run: clean all
	clear
	@echo "Executing commandExecutor"
	./$(BIN_DIR)/$(EXECUTABLE)
	
$(BIN_DIR)/$(EXECUTABLE): $(SRC_DIR)/*.cpp
	@echo "Building Application"
	$(CXX) $(CXXFLAGS) $(INC_DIR) $(LIB_DIR) $^ -o $@ $(LIBRARIES)

clean:
	@echo "Clearing..."
	-rm $(BIN_DIR)/*