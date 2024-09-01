# Define variables
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lpthread

# Target executable
TARGET = thread_pool

# Source files
SRCS = threadpool.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile each .cpp file to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
