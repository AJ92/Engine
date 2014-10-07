#include "referencecounter.h"
#include <QDebug>

ReferenceCounter::ReferenceCounter() :
   refCount(0)
{
}

void ReferenceCounter::AddRef()
{
    // Increment the reference count
    refCount++;
}

int ReferenceCounter::Release()
{
    // Decrement the reference count and
    // return the reference count.
    return --refCount;
}
