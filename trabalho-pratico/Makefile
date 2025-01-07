CC := gcc

OS   := $(shell uname -s)
ARCH := $(shell uname -m)

ifeq ($(OS),Linux)
    ifeq ($(ARCH),x86_64)
        RECOMENDADOR_OBJ := recomendador/recomendador-linux-x86_64.o
    else ifeq ($(ARCH),aarch64)  # em muitos ARM64, uname -m = aarch64
        RECOMENDADOR_OBJ := recomendador/recomendador-linux-arm64.o
    else
        $(warning Arquitetura não suportada em Linux: $(ARCH))
        RECOMENDADOR_OBJ :=
    endif
else ifeq ($(OS),Darwin)
    # Aqui assumindo x86_64 vs arm64 em macOS
    ifeq ($(ARCH),x86_64)
        RECOMENDADOR_OBJ := recomendador/recomendador-macos-x86_64.o
    else ifeq ($(ARCH),arm64)
        RECOMENDADOR_OBJ := recomendador/recomendador-arm64.o
    else
        $(warning Arquitetura não suportada em Darwin: $(ARCH))
        RECOMENDADOR_OBJ :=
    endif
else
    $(warning Sistema operativo não suportado: $(OS))
    RECOMENDADOR_OBJ :=
endif


EXEC := programa-principal
EXEC_TEST := programa-testes
EXEC_INTERATIVO := programa-interativo

FLAGS := -O3 -g -Wall -Wextra -Wunused-value `pkg-config --cflags glib-2.0`
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
all: $(EXEC) $(EXEC_TEST) $(EXEC_INTERATIVO)

$(EXEC): $(OBJ) $(RECOMENDADOR_OBJ)
	@$(CC) $(FLAGS) $^ $(LDFLAGS) -g  -o $@ ; echo "[Compiling] $@"
	
build/%.o: src/%.c
	@mkdir -p build
	@$(CC) $(FLAGS) -c $< $(INC) -o $@ ; echo "[Linking] $@"

test: $(EXEC_TEST)
	@if [ "$(DATASET_PATH)" == 0 ]; then \
	  echo -e "\033[0;31mYou should pass DATASET_PATH to the command\033[0m"; \
	else \
	  /usr/bin/time -v ./$(EXEC_TEST) $(DATASET_PATH); \
	fi

$(EXEC_INTERATIVO): $(OBJ_TEST) $(RECOMENDADOR_OBJ)
	@$(CC) $(FLAGS_TEST) $^ $(LDFLAGS) -o $@ ; echo "[Compiling] $@"

$(EXEC_TEST): $(OBJ_TEST) $(RECOMENDADOR_OBJ)
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
	@rm -f $(EXEC_INTERATIVO) ; echo "[Removing] $(EXEC_INTERATIVO)"
	@rm -f resultado.txt; echo "[Removing] resultado.txt"
	@rm -rf build/ ; echo "[Removing] build/"
	@rm -f resultados/* ; echo "[Cleaning] resultados/"
