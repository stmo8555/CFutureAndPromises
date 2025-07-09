#pragma once
#include <stdbool.h>

typedef struct cioSyncStruct cioSync;


cioSync* createCioSync();
void lock(cioSync* ctx);
void unlock(cioSync* ctx);
void waitSync(cioSync* ctx);
void signalSync(cioSync* ctx, bool wakeAll);
void freeCioSync(cioSync* ctx);

