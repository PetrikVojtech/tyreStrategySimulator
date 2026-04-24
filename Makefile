CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = main

SRCS = main.cpp \
       enduranceSimulation.cpp \
       hardCompound.cpp \
       raceCar.cpp \
       softCompound.cpp \
       trackEnvironment.cpp \
       wetTyre.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
