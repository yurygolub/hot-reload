#include <stdio.h>

#include "plugin.h"

void greet(void)
{
#ifdef _WIN32
    printf("Greetings\r\n");
#else
    printf("Greetings\n");
#endif // _WIN32
}
