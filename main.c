#include <stdio.h>
#include <stddef.h>

#include <windows.h>

#include "plugin.h"

greet_t greet = NULL;

int main(void)
{
    const char *plugin_file_name = "plugin.dll";
    HMODULE hModule = LoadLibraryW(plugin_file_name);
    if (hModule == NULL)
    {
        fprintf(stderr, "ERROR: could not load %s", plugin_file_name);
        return 1;
    }

    const char *greet_func_name = "greet";
    greet_t greet = (greet_t)GetProcAddress(hModule, greet_func_name);
    if (greet == NULL)
    {
        fprintf(stderr, "ERROR: could not find %s symbol in %s", greet_func_name, plugin_file_name);
        return 1;
    }

    greet();

    return 0;
}
