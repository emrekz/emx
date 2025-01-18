# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c17 -Wno-missing-braces
FILE = run

# Directories
SRC_DIR = src

# Gather all source and header files
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")
TEST_FILES = $(shell find $(SRC_DIR) -type f -name "test.c")
OBJ_FILES = $(SRC_FILES:.c=.o)

# Include path
CUSTOM_INC_PATH ?= ./include
INC_PATH = -I. -I${CUSTOM_INC_PATH}

# Build Rules
all:
	${CC} ${CGLAGS} ${SRC_FILES} ${INC_PATH} -o ${FILE}
#	./${FILE}.exe

# Test
test:
	${CC} ${CGLAGS} ${TEST_FILES} ${INC_PATH} -o ${FILE}
	./${FILE}.exe
