CC=clang

C_FLAGS=-Wall -Wextra -O0 -g

all:
	@mkdir -p build
	$(CC) $(C_FLAGS) -c -o build/plugin.lib plugin.c
	$(CC) $(C_FLAGS) -o build/main.exe main.c -L build -l plugin
