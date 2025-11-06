CC=clang

DEBUG_FLAGS=-O0 -g
OPT=-Os

C_FLAGS=-Wall -Wextra

ifeq ($(CONFIG),debug)
    C_FLAGS += $(DEBUG_FLAGS)
else
    C_FLAGS += $(OPT)
endif

all:
	@mkdir -p build
	$(CC) $(C_FLAGS) -o build/plugin.dll -shared plugin.c
	$(CC) $(C_FLAGS) -o build/main.exe main.c
