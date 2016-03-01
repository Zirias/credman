#ifndef UTILS_STRINGFUNC_H
#define UTILS_STRINGFUNC_H

typedef struct StringFunc StringFunc;
struct StringFunc
{
    const char *(*Invoke)(StringFunc *self);
    void (*Destroy)(StringFunc *self);
};

#endif
