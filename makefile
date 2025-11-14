DEBUG_FLAGS=-O0 -g
OPT=-Os

C_FLAGS=-Wall -Wextra

PLUGIN=plugin.dll
BIN=main.exe

ifneq ($(CC),clang)
    OPT += -s
    PLUGIN=plugin.so
    BIN=main
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
