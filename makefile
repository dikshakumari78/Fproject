# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

# Target executable
TARGET = thread_pool_cpp

# Source files
SRCS = thread_pool.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: clean
