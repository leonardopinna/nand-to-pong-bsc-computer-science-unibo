CC := gcc
SRC_DIR := .
OBJ_DIR := .
OUTPUT_DIR := .
EXECUTABLE := assembler

# Find all .c files in the src folder
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Generate corresponding .o file names in the obj folder
OBJ_FILES := $(patsubst $(SRC_DIR)/**/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

CFLAGS := -Wall -Wextra
LDFLAGS :=

# Include directories
INCLUDES := -I $(SRC_DIR)/headers
CFLAGS += $(INCLUDES)

# Build rule for the executable
$(EXECUTABLE): $(OBJ_FILES) | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	@echo "Build successful"

clean: 
	rm assembler output.hack