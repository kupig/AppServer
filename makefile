
CXX?=g++
MAKE?=make
CFLAG=-g -Wall -O0

SOURCE:=$(shell find IGMainProject -name "*.cpp")
TARGET=$(SOURCE:.cpp=.o)

LIBS=IGLibProject/Tutorial1 \
	 IGLibProject/Tutorial2 \
	 IGLibProject/NetPlugin

LIBS_DIR=$(LIBS:=.SUBDIR)

OBJECT=Bin/IGLoader

all: $(OBJECT) $(LIBS_DIR)
	@echo "All make done!!"

$(LIBS_DIR):%.SUBDIR:%
	$(MAKE) -C $^

$(OBJECT):$(TARGET)
	$(CXX) $(CFLAG) -o $@ $^ -ldl
	
%.o:%.cpp
	$(CXX) $(CFLAG) -MMD -c -o $@ $< -std=gnu++11

-include $(SOURCE:.cpp=.d)

.PHONY:all clean $(LIBS_DIR)

clean:
	rm $(shell find IGMainProject -name "*.o")
	rm $(shell find IGLibProject -name "*.o")
	rm $(shell find IGMainProject -name "*.d")
	rm $(shell find IGLibProject -name "*.d")
	rm $(shell find Bin  -name "*.so")
	rm $(shell find Bin  -name "IGLoader")
