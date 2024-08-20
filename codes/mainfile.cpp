# Makefile
# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra
# Target executable
TARGET = file_manager
# Source files
SRCS = main.cpp FileManager.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)
# Default rule
all: $(TARGET)
# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)
# Phony targets
PHONY: all clean
