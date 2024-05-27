# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -O2 -std=c++17 -I src
CXXLINKFLAGS := 

# Directories
SRCDIR := src
OBJDIR := obj
DEPDIR := dep

# File extensions
SRCEXT := cpp
DEPEXT := d
OBJEXT := o

# Collect all source files
SOURCES := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')

# Generate object files and dependency files paths
OBJECTS := $(SOURCES:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.$(OBJEXT))
DEPS := $(OBJECTS:$(OBJDIR)/%.$(OBJEXT)=$(DEPDIR)/%.$(DEPEXT))

# Output executable name
TARGET := mincut

# Default target
all: $(TARGET)

# Link the program
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXLINKFLAGS) $(OBJECTS) -o $@

# Compile source files to object files and generate dependencies
$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEPDIR)/$*)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
	@mv $(OBJDIR)/$*.$(DEPEXT) $(DEPDIR)/$*.$(DEPEXT)

# Include the dependency files
-include $(DEPS)

# Clean up generated files
clean:
	rm -rf $(OBJDIR) $(DEPDIR) $(TARGET)

# Phony targets
.PHONY: all clean
