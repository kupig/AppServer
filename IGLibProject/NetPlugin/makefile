#########################################################

CXX?=g++
CFLAG= -g -Wall -O0
	
TARGET=../../Bin/libNetPlugin.so

SOURCE=$(shell find . -name "*.cpp")
OBJECT=$(SOURCE:.cpp=.o)
ALIB=$(-L./Libevent -levent -levent_core.a -levent_extra.a -levent_pthreads.a)
#########################################################  

all:$(TARGET) 
		@echo "make lib network plugin done!!"

$(TARGET):$(OBJECT)
		$(CXX) $(CFLAG) -shared -o $@ $^

%.o:%.cpp
		$(CXX) $(CFLAG) -fPIC -MMD -c -o $@ $< -std=gnu++11

-include $(SOURCE:.cpp=.d)

#########################################################  

clean:
		#rm $(TARGET) $(OBJECT) $(SOURCE:.cpp=.d) $(EXEC)

#########################################################
