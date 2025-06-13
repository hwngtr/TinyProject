# Compiler and flags
CXX = g++
# Add -Iinclude to tell g++ where to find header files (.hpp)
CXXFLAGS = -std=c++17 -O2 -Iinclude 

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Executable name
TARGET = $(BUILDDIR)/simple_demo

# Find all .cpp files in the source directory
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# Create a list of object files to be placed in the build directory
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Rule to build the executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile .cpp files into .o files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean the build directory
clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean run