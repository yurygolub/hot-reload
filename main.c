#include <stdio.h>
#include <stddef.h>

#include <windows.h>

typedef void (*greet_t)(void);

greet_t greet = NULL;

int main(void)
{
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

    greet();

    return 0;
}
