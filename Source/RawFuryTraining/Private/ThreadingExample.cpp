#include "ThreadingExample.h"

ThreadingExample::ThreadingExample(int32 MaxPrimeNumber)
{
    // Pass the information from the constructor arguments to this instance's variables.
    UpperLimit = MaxPrimeNumber;
}

void ThreadingExample::DoWork()
{
    SCOPED_NAMED_EVENT_TEXT("ThreadingExample::DoWork", FColor::Purple);

    int32 PrimeNumberCount = 1;
    for (int32 i = 1; i <= UpperLimit; i++)
    {
        bool bIsPrime = true;

        for (int32 j = 2; j < i / 2; j++)
        {
            if (i % j == 0)
            {
                bIsPrime = false;
                break;
            }
        }

        if (bIsPrime)
        {
            UE_LOG(LogTemp, Warning, TEXT("Prime number # %ld: %ld"), PrimeNumberCount, i);
            PrimeNumberCount++;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("TASK DONE!"));
}