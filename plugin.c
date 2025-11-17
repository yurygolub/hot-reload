#include <stdio.h>

#ifdef _WIN32
#include "plugin.h"
#endif // _WIN32

void greet(void)
{
#ifdef _WIN32
    printf("Greetings\r\n");
#else
    printf("Greetings\n");
#endif // _WIN32
}
