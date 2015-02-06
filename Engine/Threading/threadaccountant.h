#ifndef THREADACCOUNTANT_H
#define THREADACCOUNTANT_H

#include "Object/object.h"

class ThreadAccountant : public Object
{
public:
    ThreadAccountant(int maxThreads);
    virtual ~ThreadAccountant();

    bool addThread();
    bool removeThread();

    int getMaxThreadCount();
    int getThreadsInUseCount();

private:
    int maxThreads;
    int threadsInUse;
};

#endif // THREADACCOUNTANT_H
