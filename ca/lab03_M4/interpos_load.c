#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

void bill(char *arg)
{
    printf("interpos bill: bill is called with %s\n", arg);
    void (*real_bill)(char *) = dlsym(RTLD_NEXT, "bill");
    real_bill(arg);
}

void sam(double arg)
{
    printf("interpos sam: sam is called with %.2f\n", arg);
    void (*real_sam)(double) = dlsym(RTLD_NEXT, "sam");
    real_sam(arg);
}
