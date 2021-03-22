#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"

// Example multi threading work that prints the prime numbers smaller than MaxPrimeNumber to the console.

class ThreadingExample : public FNonAbandonableTask
{
public:
    // Constructor which we need to call and provide information to start the task.
    ThreadingExample(int32 MaxPrimeNumber);

    void DoWork();

public:
    FORCEINLINE TStatId GetStatId()
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(ThreadingExample, STATGROUP_ThreadPoolAsyncTasks);
    }

private:
    int32 UpperLimit;
};