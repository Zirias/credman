#ifndef CREDMODEL_CRED_H
#define CREDMODEL_CRED_H

#include <time.h>

typedef struct Cred Cred;

Cred * Cred_create(void);
void Cred_destroy(Cred *self);

const char * Cred_username(const Cred *self);
const char * Cred_password(const Cred *self);
const char * Cred_description(const Cred *self);
time_t Cred_created(const Cred *self);
time_t Cred_changed(const Cred *self);

void Cred_setUsername(Cred *self, const char *username);
void Cred_setPassword(Cred *self, const char *password);

#endif
