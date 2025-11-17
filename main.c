#include <stdio.h>
#include <stddef.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include "plugin.h"
#endif // _WIN32

#ifdef _WIN32
typedef void (*greet_t)(void);
#else
greet_t greet = NULL;
#endif // _WIN32

int main(void)
{
#ifdef _WIN32
    const char *plugin_file_name = "plugin.dll";
    void *plugin = NULL;

    if (plugin != NULL)
    {
        FreeLibrary(plugin);
    }

    printf("INFO: loading library '%s'\r\n", plugin_file_name);
    plugin = LoadLibrary(plugin_file_name);
    if (plugin == NULL)
    {
        fprintf(stderr, "ERROR: could not load '%s'\r\n", plugin_file_name);
        return 1;
    }

    const char *greet_func_name = "greet";
    printf("INFO: loading symbol '%s'\r\n", greet_func_name);
    greet_t greet = (greet_t)GetProcAddress(plugin, greet_func_name);
    if (greet == NULL)
    {
        fprintf(stderr, "ERROR: could not find '%s' symbol in '%s'\r\n", greet_func_name, plugin_file_name);
        return 1;
    }
#else
    const char *plugin_file_name = "plugin.so";
    void *handle = dlopen(plugin_file_name, RTLD_NOW);
    if (handle == NULL)
    {
        fprintf(stderr, "ERROR: could not load %s: %s\n", plugin_file_name, dlerror());
        return 1;
    }

    const char *greet_func_name = "greet";
    greet_t greet = (greet_t)dlsym(handle, greet_func_name);
    if (greet == NULL)
    {
        fprintf(stderr, "ERROR: could not find %s symbol in %s\n", greet_func_name, plugin_file_name);
        return 1;
    }
#endif // _WIN32

    greet();

    return 0;
}
