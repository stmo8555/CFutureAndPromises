#pragma once
#include <stdbool.h>

typedef struct cioSyncStruct cioSync;


cioSync* createCioSync();
void lock(cioSync* ctx);
void unlock(cioSync* ctx);
void wait(cioSync* ctx);
void signal(cioSync* ctx, bool wakeAll);
void freeCioSync(cioSync* ctx);

