
CXX=g++
CFLAG=-g -Wall

OBJECT=TestClient
SOURCE=$(shell find . -name "*.cpp")
SOURCE+=../../IGLibProject/NetPlugin/IGNetManager.cpp

TARGET=$(SOURCE:.cpp=.o)

PLATFORM =$(shell uname -s)
LINUX=Linux

$(OBJECT) : $(TARGET)
ifeq ($(LINUX), $(PLATFORM))
	$(CXX) $(CFLAG)  -o $@ $^ -L../../Bin/Libevent -levent
else
	$(CXX) $(CFLAG)  -o $@ $^ -levent
endif

%.o:%.cpp
	$(CXX) $(CFLAG) -MMD -c -o $@ $< -std=gnu++11

-include $(SOUCE:.cpp=.d)

clean:
	rm *.o *.d $(OBJECT)
