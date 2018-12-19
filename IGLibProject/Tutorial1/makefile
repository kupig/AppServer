#########################################################

CXX?=g++
CFLAG= -g -Wall 

TARGET=../../Bin/libTutorial1.so

SOURCE=$(shell find . -name "*.cpp")
OBJECT=$(SOURCE:.cpp=.o)

#########################################################  

all:$(TARGET) 
	@echo "make lib Tutorial done!!"

$(TARGET):$(OBJECT)
	$(CXX) $(CFLAG) -shared -o $@ $^

%.o:%.cpp
	$(CXX) $(CFLAG) -fPIC -MMD -c -o $@ $<

-include $(SOURCE:.cpp=.d)

#########################################################  

clean:
	#rm $(TARGET) $(OBJECT) $(SOURCE:.cpp=.d) $(EXEC)

#########################################################
