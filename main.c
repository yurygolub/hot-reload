#include <stdio.h>
#include <stddef.h>

#include <windows.h>

typedef void (*greet_t)(void);

greet_t greet = NULL;

int main(void)
{
    const LPCWSTR plugin_file_name = L"plugin.dll";
    printf("INFO: loading library '%ls'\r\n", plugin_file_name);
    HMODULE hModule = LoadLibraryW(plugin_file_name);
    if (hModule == NULL)
    {
        fprintf(stderr, "ERROR: could not load '%ls'\r\n", plugin_file_name);
        return 1;
    }

    const LPCSTR greet_func_name = "greet";
    printf("INFO: loading symbol '%s'\r\n", greet_func_name);
    greet_t greet = (greet_t)GetProcAddress(hModule, greet_func_name);
    if (greet == NULL)
    {
        fprintf(stderr, "ERROR: could not find '%s' symbol in '%ls'\r\n", greet_func_name, plugin_file_name);
        return 1;
    }

    greet();

    return 0;
}
