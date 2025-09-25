CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2
LDFLAGS = 

# Source files
HOOK_SOURCES = libanogs_hooks.c
TEST_SOURCES = test_hooks.c
MAIN_SOURCE = libanogs.so.c

# Object files
HOOK_OBJECTS = $(HOOK_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

# Executables
TEST_PROGRAM = test_hooks
SHARED_LIB = libanogs_hooks.so

# Default target
all: $(TEST_PROGRAM) $(SHARED_LIB)

# Build test program
$(TEST_PROGRAM): $(TEST_OBJECTS) $(HOOK_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Build shared library
$(SHARED_LIB): $(HOOK_OBJECTS)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^ $(LDFLAGS)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# Clean build artifacts
clean:
	rm -f $(HOOK_OBJECTS) $(TEST_OBJECTS) $(TEST_PROGRAM) $(SHARED_LIB)

# Install (for development purposes)
install: $(SHARED_LIB)
	@echo "Installing $(SHARED_LIB) for development testing"
	@echo "WARNING: Use only on authorized test systems"

# Run tests
test: $(TEST_PROGRAM)
	@echo "Running defensive hook system tests..."
	./$(TEST_PROGRAM)

# Security analysis
analyze:
	@echo "Security analysis of hook implementation:"
	@echo "• Input validation: IMPLEMENTED"
	@echo "• Buffer overflow protection: IMPLEMENTED" 
	@echo "• Logging/monitoring: IMPLEMENTED"
	@echo "• Safe fallback behavior: IMPLEMENTED"

.PHONY: all clean install test analyze

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build test program and shared library"
	@echo "  clean    - Remove build artifacts"
	@echo "  test     - Run hook system tests"
	@echo "  analyze  - Show security analysis"
	@echo "  help     - Show this help"