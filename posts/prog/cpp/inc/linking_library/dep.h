#ifndef DEP_H
#define DEP_H

typedef struct api_s {
    const char *name;
    void (*show)(void);
    int (*sum)(int a, int b);
    int (*sub)(int a, int b);
} api_t;

void show(void);
int sub(int a, int b);
int sum(int a, int b);

#endif
