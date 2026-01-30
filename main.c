#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include "plugin.h"
#endif // _WIN32

#ifdef _WIN32
typedef void (*greet_t)(void);
static const char *plugin_file_name = "plugin.dll";
#else
static const char *plugin_file_name = "plugin.so";
#endif // _WIN32

static void *plugin = NULL;
static greet_t greet = NULL;

bool reload_plugin(void)
{
#ifdef _WIN32
    if (plugin != NULL)
    {
        printf("INFO: freeing library '%s'\r\n", plugin_file_name);
        FreeLibrary(plugin);
    }

    printf("INFO: loading library '%s'\r\n", plugin_file_name);
    plugin = LoadLibrary(plugin_file_name);
    if (plugin == NULL)
    {
        fprintf(stderr, "ERROR: could not load '%s'\r\n", plugin_file_name);
        return false;
    }

    const char *greet_func_name = "greet";
    printf("INFO: loading symbol '%s'\r\n", greet_func_name);
    greet = (greet_t)GetProcAddress(plugin, greet_func_name);
    if (greet == NULL)
    {
        fprintf(stderr, "ERROR: could not find '%s' symbol in '%s'\r\n", greet_func_name, plugin_file_name);
        return false;
    }
#else
    plugin = dlopen(plugin_file_name, RTLD_NOW);
    if (plugin == NULL)
    {
        fprintf(stderr, "ERROR: could not load %s: %s\n", plugin_file_name, dlerror());
        return false;
    }

    const char *greet_func_name = "greet";
    greet = (greet_t)dlsym(plugin, greet_func_name);
    if (greet == NULL)
    {
        fprintf(stderr, "ERROR: could not find %s symbol in %s\n", greet_func_name, plugin_file_name);
        return false;
    }
#endif // _WIN32

    return true;
}

int main(void)
{
    if (!reload_plugin()) return 1;

    greet();
    printf("Press Enter to continue...");
    getchar();

    if (!reload_plugin()) return 1;
    greet();

    return 0;
}
