#include "FutureAndPromises.h"
#include <stdio.h>
#include <memory.h>
#include <windows.h>
#include <stdlib.h>

// Struct to pass multiple arguments into the thread
typedef struct {
    LPVOID lpParam;
    Promise* promise;
} ThreadArgs;

// Thread function
DWORD WINAPI ThreadEntry(LPVOID lpParam) {
    ThreadArgs* args = (ThreadArgs*)lpParam;

    int i = 0;
    for (; i < 5; ++i) {
        printf("%d\n", i);
        Sleep(1000);  // Sleep 1 second
    }

    void* val = malloc(sizeof(int));
    if (!val) {
        printf("Failed to allocate memory for value\n");
        abort();
    }

    *((int*)val) = i;

    // Set the value in the promise
    promiseSetValue(args->promise, val);

    free(args);  // Free the ThreadArgs struct

    return 0;
}

// Main program
int main() 
{
    Promise* promise = promiseCreate();
    Future* future = getFuture(promise);
    // Prepare arguments for the thread
    ThreadArgs* args = malloc(sizeof(ThreadArgs));
    if (!args) {
        printf("Failed to allocate memory for thread args\n");
        free(promise);
        free(future);
        return 1;
    }

    args->lpParam = NULL;      // Use if needed
    args->promise = promise;

    // Create the thread
    HANDLE threadHandle = CreateThread(
        NULL,
        0,
        ThreadEntry,
        args,
        0,
        NULL
    );

    if (threadHandle == NULL) {
        printf("Failed to create thread. Error: %lu\n", GetLastError());
        free(args);
        free(promise);
        free(future);
        return 1;
    }

    int result =  *(int*)futureGetValue(future);
    printf("Result is %d\n", result);

    // Wait for the thread to complete
    WaitForSingleObject(threadHandle, INFINITE);

    printf("thread is done\n");
    // Close thread handle
    CloseHandle(threadHandle);

    free(promise);
    free(future);

    return 0;
}