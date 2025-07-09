#pragma once


typedef struct PromiseStruct Promise;

typedef struct FutureStruct Future;


void futureWait(Future* future);

void* futureGetValue(Future* future);

Future* getFuture(Promise* promise);

void promiseSetValue(Promise* promise, void* val);

Promise* promiseCreate();

void promiseDestroy(Promise* promise);
void futureDestroy(Future* future);
