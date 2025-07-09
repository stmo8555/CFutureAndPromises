#include "FutureAndPromises.h"
#include "cioSync.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct PromiseStruct
{
    void* Value;
    bool Ready;
    cioSync* CioSync;
} Promise;

typedef struct FutureStruct
{
    void** Value;
    bool* Ready;
    cioSync* CioSync;
} Future;


void futureWait(Future *future)
{
    lock(future->CioSync);
    while (!*future->Ready)
    {
        waitSync(future->CioSync);
    }
    unlock(future->CioSync);
}

void* futureGetValue(Future *future)
{
    futureWait(future);
    return *future->Value;
}

Future* getFuture(Promise *promise)
{
    Future* tmp = (Future*)malloc(sizeof(Future));
    if (!tmp)
    {
        printf("Failed to create promise");
        return NULL;
    }

    tmp->CioSync = promise->CioSync;
    tmp->Ready = &promise->Ready;
    tmp->Value = &promise->Value;

    return tmp;
}

void promiseSetValue(Promise *promise, void* val)
{
    lock(promise->CioSync);
    promise->Ready = true;
    promise->Value = val;
    signalSync(promise->CioSync, false);
    unlock(promise->CioSync);
}

Promise* promiseCreate()
{
    Promise* tmp = (Promise*)malloc(sizeof(Promise));
    if (!tmp)
    {
        printf("Failed to create promise");
        return NULL;
    }
    tmp->Ready = false;
    tmp->Value = NULL;
    tmp->CioSync = createCioSync();
    return tmp;
}

void promiseDestroy(Promise *promise)
{
    freeCioSync(promise->CioSync);
    free(promise);
}

void futureDestroy(Future *future)
{
    freeCioSync(future->CioSync);
    free(future);
}
