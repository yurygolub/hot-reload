DEBUG_FLAGS=-O0 -g
OPT=-Os

C_FLAGS=-Wall -Wextra

ifneq ($(CC),clang)
    OPT += -s
endif

ifeq ($(CONFIG),debug)
    C_FLAGS += $(DEBUG_FLAGS)
else
    C_FLAGS += $(OPT)
endif

all:
	@mkdir -p build
	$(CC) $(C_FLAGS) -o build/plugin.so -shared plugin.c
	$(CC) $(C_FLAGS) -o build/main main.c
