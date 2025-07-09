#include "cioSync.h"
#define _WIN32_WINNT 0x0600
#include <windows.h>


typedef struct cioSyncStruct
{
    CRITICAL_SECTION lock;
    CONDITION_VARIABLE cond;

} cioSync;


cioSync* createCioSync()
{
    cioSync* tmp = (cioSync*)malloc(sizeof(cioSync));
    if (!tmp)
        return NULL;
    
    InitializeCriticalSection(&tmp->lock);
    InitializeConditionVariable(&tmp->cond);

    return tmp;
}

void lock(cioSync* ctx)
{
    EnterCriticalSection(&ctx->lock);
}

void unlock(cioSync* ctx)
{
    LeaveCriticalSection(&ctx->lock);
}

void waitSync(cioSync* ctx)
{
    SleepConditionVariableCS(&ctx->cond, &ctx->lock, INFINITE);
}

void signalSync(cioSync* ctx, bool wakeAll)
{
    if (wakeAll)
        WakeAllConditionVariable(&ctx->cond);
    else
        WakeConditionVariable(&ctx->cond);
}

void freeCioSync(cioSync *ctx)
{
    free(ctx);
}
