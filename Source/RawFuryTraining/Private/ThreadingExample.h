#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"

class ThreadingExample : public FNonAbandonableTask
{
public:
    // Constructor which we need to call and provide information to start the task.
    ThreadingExample(int32 MaxPrimeNumber);

    FORCEINLINE TStatId GetStatId()
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(ThreadingExample, STATGROUP_ThreadPoolAsyncTasks);
    }

    void DoWork();

private:
    int32 UpperLimit;
};