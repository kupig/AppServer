#########################################################

CC=g++
CFLAG= -g -Wall 

TARGET=../Bin/libTutorial1.so

SOURCE=$(shell find . -name "*.cpp")
OBJECT=$(SOURCE:.cpp=.o)

#########################################################  

all:$(TARGET) 

$(TARGET):$(OBJECT)
	$(CC) $(CFLAG) -shared -o $@ $^

%.o:%.cpp
	$(CC) $(CFLAG) -fPIC -MMD -c -o $@ $<

-include $(SOURCE:.cpp=.d)

#########################################################  

clean:
	#rm $(TARGET) $(OBJECT) $(SOURCE:.cpp=.d) $(EXEC)

#########################################################
