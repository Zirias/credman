#include "cred.h"

struct Cred
{
    const char *username;
    const char *password;
    time_t created;
    time_t changed;
};

Cred *
Cred_create(void)
{
    Cred *self
}
