#########################################################

CXX?=g++
CFLAG= -g -Wall -O0
	
TARGET=../../Bin/libNetPlugin.so

SOURCE=$(shell find . -name "*.cpp")
OBJECT=$(SOURCE:.cpp=.o)
#########################################################  

all:$(TARGET) 
		@echo "make lib network plugin done!!"

$(TARGET):$(OBJECT)
		#$(CXX) $(CFLAG) -shared -o $@ $^ -levent
		$(CXX) $(CFLAG) -shared -o $@ $^  -levent -levent_core -levent_extra


%.o:%.cpp
		$(CXX) $(CFLAG) -fPIC -MMD -c -o $@ $< -std=gnu++11

-include $(SOURCE:.cpp=.d)

#########################################################  

clean:
		#rm $(TARGET) $(OBJECT) $(SOURCE:.cpp=.d) $(EXEC)
	rm *.o *.d

#########################################################
