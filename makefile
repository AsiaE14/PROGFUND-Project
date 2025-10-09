# ===== Makefile =====

# Compiler & flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Executables
MAIN = main
UNIT = test_unit
E2E  = test_e2e

# Source files
MAIN_SRC = main.c
UNIT_SRC = test_unit.c
E2E_SRC  = test_e2e.c

# Default target (run main)
all: $(MAIN)

# Build main program
$(MAIN): $(MAIN_SRC)
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $(MAIN)

# Build Unit test
$(UNIT): $(MAIN_SRC) $(UNIT_SRC)
	$(CC) $(CFLAGS) -DTEST_MODE $(MAIN_SRC) $(UNIT_SRC) -o $(UNIT)

$(E2E): $(MAIN_SRC) $(E2E_SRC)
	$(CC) $(CFLAGS) -DTEST_MODE $(MAIN_SRC) $(E2E_SRC) -o $(E2E)


# Run tests
test: $(UNIT) $(E2E)
	@echo "Running Unit Tests..."
	@./$(UNIT)
	@echo "Running E2E Tests..."
	@./$(E2E)

# Clean build files
clean:
	rm -f $(MAIN) $(UNIT) $(E2E)
	rm -f *.o
	rm -f test_data.csv
	rm -f temp_test.csv

.PHONY: all clean test