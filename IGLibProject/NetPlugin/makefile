#########################################################

CXX?=g++
CFLAG= -g -Wall -O0
	
TARGET=../../Bin/libNetPlugin.so

SOURCE=$(shell find . -name "*.cpp")
OBJECT=$(SOURCE:.cpp=.o)

PLATFORM =$(shell uname -s)

LINUX = Linux
#########################################################  

all:$(TARGET) 
		@echo "make lib network plugin done!!"

$(TARGET):$(OBJECT)
ifeq ($(LINUX), $(PLATFORM))
		$(CXX) $(CFLAG) -shared -o $@ $^ -L../../Bin/Libevent/ -levent
else
		echo $(LINUX)
		echo $(PLATFORM)
		$(CXX) $(CFLAG) -shared -o $@ $^  -levent -levent_core -levent_extra
endif

%.o:%.cpp
		$(CXX) $(CFLAG) -fPIC -MMD -c -o $@ $< -std=gnu++11

-include $(SOURCE:.cpp=.d)

#########################################################  

clean:
		#rm $(TARGET) $(OBJECT) $(SOURCE:.cpp=.d) $(EXEC)
	rm *.o *.d

#########################################################
