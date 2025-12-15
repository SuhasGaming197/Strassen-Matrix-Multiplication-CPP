# Makefile
CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17
TARGET = StrassenOptimizedApp
SRCS = main.cpp StrassenOptimizer.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
