#########################################################

CXX?=g++
CFLAG= -g -Wall -O0

TARGET=../../Bin/libTutorial2.so

SOURCE=$(shell find . -name "*.cpp")
OBJECT=$(SOURCE:.cpp=.o)

#########################################################  

all:$(TARGET) 
	@echo "make lib Tutorial2 done!!"

$(TARGET):$(OBJECT)
	$(CXX) $(CFLAG) -shared -o $@ $^

%.o:%.cpp
	$(CXX) $(CFLAG) -fPIC -MMD -c -o $@ $< -std=gnu++11

-include $(SOURCE:.cpp=.d)

#########################################################  

clean:
	#rm $(TARGET) $(OBJECT) $(SOURCE:.cpp=.d) $(EXEC)

#########################################################
