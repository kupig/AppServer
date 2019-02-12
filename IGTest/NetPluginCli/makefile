
CXX=g++
CFLAG=-g -Wall

OBJECT=TestClient
SOURCE=$(shell find . -name "*.cpp")
SOURCE+=../../IGLibProject/NetPlugin/IGNetManager.cpp

TARGET=$(SOURCE:.cpp=.o)

$(OBJECT) : $(TARGET)
	$(CXX) $(CFLAG)  -o $@ $^ -L../../Bin/Libevent -levent

%.o:%.cpp
	$(CXX) $(CFLAG) -MMD -c -o $@ $< -std=gnu++11

-include $(SOUCE:.cpp=.d)

clean:
	rm *.o *.d $(OBJECT)
