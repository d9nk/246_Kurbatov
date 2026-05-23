#include <stdio.h>

void __real_fred(int arg);
void __real_john(double arg);

void __wrap_fred(int arg)
{
    printf("__wrap_fred: fred is called with %d\n", arg);
    __real_fred(arg);
}

void __wrap_john(double arg)
{
    printf("__wrap_john: john is called with %.2f\n", arg);
    __real_john(arg);
}
