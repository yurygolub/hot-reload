DEBUG_FLAGS=-O0 -g
OPT=-Os

C_FLAGS=-Wall -Wextra

ifneq ($(CC),clang)
    OPT += -s
endif

ifeq ($(OS),Windows_NT)
    PLUGIN=plugin.dll
    BIN=main.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        PLUGIN=plugin.so
        BIN=main
    else
        $(error platform not supported)
    endif
endif

ifeq ($(CONFIG),debug)
    C_FLAGS += $(DEBUG_FLAGS)
else
    C_FLAGS += $(OPT)
endif

all:
	@mkdir -p build
	$(CC) $(C_FLAGS) -o build/$(PLUGIN) -shared plugin.c
	$(CC) $(C_FLAGS) -o build/$(BIN) main.c
