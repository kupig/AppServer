#########################################################

CC=g++
CFLAG= -g -Wall 

TARGET=libTutorial1.so

SOURCE=$(shell find . -name "*.cpp")
OBJECT=$(SOURCE:.cpp=.o)

#########################################################  

all:$(TARGET) 
	mv $(TARGET) ../../Bin/
	mv $(OBJECT) ../../Bin/
	mv $(SOURCE:.cpp=.d) ../../Bin/

$(TARGET):$(OBJECT)
	$(CC) $(CFLAG) -shared -o $@ $^

%.o:%.cpp
	$(CC) $(CFLAG) -fPIC -MMD -c -o $@ $<

-include $(SOURCE:.cpp=.d)

#########################################################  

clean:
	#rm $(TARGET) $(OBJECT) $(SOURCE:.cpp=.d) $(EXEC)

#########################################################
