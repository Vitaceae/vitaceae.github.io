#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <dlfcn.h>
#include <link.h>

#include "dep.h"


int main()
{
    void *handle;
    const char *soname = "libdep.so.1";
    api_t *api;

    handle = dlopen(soname, RTLD_LAZY);

    if (!handle) {
        printf("dlopen: %s\n", dlerror());
        return -1;
    }

    api = dlsym(handle, "api");
    if (!api) {
        printf("dlsym(api): %s\n", dlerror());
    } else {
        printf("API name = %s\n", api->name);
        printf("test sum(2, 3): %d\n", api->sum(2, 3));
    }

    void (*show)(void);
    //*(void **)(&show) = dlsym(handle, "show");
    *(void **)(&show) = dlvsym(handle, "show", "API_1.1");
    if (!show) {
        printf("dlopen(show): %s\n", dlerror());
    } else {
        show();
    }

    dlclose(handle);
}
