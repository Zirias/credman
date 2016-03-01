#ifndef CREDMODEL_CRED_H
#define CREDMODEL_CRED_H

#include <time.h>

typedef struct Cred Cred;

Cred *Cred_Create(void);
Cred *Cred_Copy(const Cred *rhs);
void Cred_Destroy(Cred *self);

const char * Cred_Username(const Cred *self);
const char * Cred_Password(const Cred *self);
const char * Cred_Description(const Cred *self);
time_t Cred_Created(const Cred *self);
time_t Cred_Changed(const Cred *self);

void Cred_SetUsername(Cred *self, const char *username);
void Cred_SetPassword(Cred *self, const char *password);
void Cred_SetDescription(Cred *self, const char *description);

#endif
