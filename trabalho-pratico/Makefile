CC := gcc

EXEC := programa-principal
EXEC_TEST := programa-testes

FLAGS := -Wall -Wextra -Wunused-parameter -Wunused-value `pkg-config --cflags glib-2.0`
FLAGS_TEST := $(FLAGS) -Wno-unused-function

INC := -Iinclude/
INC_TEST := $(INC)
SRC := $(shell find src/ -name "*.c")
OBJ := $(SRC:src/%.c=build/%.o)

SRC_TEST := $(SRC)
OBJ_TEST := $(OBJ)

INCLUDE_FILES := $(shell find include/ -name "*.h")

DATASET_PATH ?= 0
QUERIES_PATH ?= 0

LDFLAGS := `pkg-config --libs glib-2.0`

.SUFFIXES:

.PHONY: all
all: $(EXEC) $(EXEC_TEST)

$(EXEC): $(OBJ)
	@$(CC) $(FLAGS) $^ $(LDFLAGS) -g -o $@ ; echo "[Compiling] $@"
	
build/%.o: src/%.c
	@mkdir -p build
	@$(CC) $(FLAGS) -c $< $(INC) -o $@ ; echo "[Linking] $@"

test: $(EXEC_TEST)
	@if [ "$(DATASET_PATH)" == 0 ]; then \
	  echo -e "\033[0;31mYou should pass DATASET_PATH to the command\033[0m"; \
	else \
	  /usr/bin/time -v ./$(EXEC_TEST) $(DATASET_PATH); \
	fi

$(EXEC_TEST): $(OBJ_TEST)
	@$(CC) $(FLAGS_TEST) $^ $(LDFLAGS) -o $@ ; echo "[Compiling] $@"

build/%.o: tests/%.c
	@mkdir -p build
	@$(CC) $(FLAGS_TEST) -c $< $(INC_TEST) -o $@ ; echo "[Linking] $@"

.PHONY: leaks
leaks: $(EXEC)
	@if [ "$(DATASET_PATH)" == 0 ] || [ "$(QUERIES_PATH)" == 0 ]; then \
	  echo -e "\033[0;31mYou should pass DATASET_PATH and QUERIES_PATH to the command\033[0m"; \
	else \
	 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(EXEC) $(DATASET_PATH) $(QUERIES_PATH); \
	fi

.PHONY: clean
clean:
	@rm -f $(EXEC) ; echo "[Removing] $(EXEC)"
	@rm -f $(EXEC_TEST) ; echo "[Removing] $(EXEC_TEST)"
	@rm -rf build/ ; echo "[Removing] build/"
	@rm -f resultados/* ; echo "[Cleaning] resultados/"
