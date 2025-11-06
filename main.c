#include <stdio.h>
#include <stddef.h>

#include <dlfcn.h>

#include "plugin.h"

greet_t greet = NULL;

int main(void)
{
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

    greet();

    return 0;
}
