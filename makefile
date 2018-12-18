
CC=g++
CFLAG=-g -Wall

SOURCE:=$(shell find . -name "*.cpp")
TARGET=$(SOURCE:.cpp=.o)
OBJECT=IGLoader

all: $(OBJECT)
	-mv $(TARGET) ./Bin	
	-mv $(SOURCE:.cpp=.d) ./Bin	
	-mv $(OBJECT) ./Bin	

$(OBJECT):$(TARGET)
	$(CC) $(CFLAG) -o $@ $^ -ldl
	
%.o:%.cpp
	$(CC) $(CFLAG) -MMD -c -o $@ $< 

-include $(TARGET_MMD)

clean:
	rm ./Bin/$(OBJECT) ./Bin/*.o ./Bin/*.d ./Bin/*.so
