#include "threadaccountant.h"


ThreadAccountant::ThreadAccountant(int maxThreads) :
    Object()
{
    if(maxThreads < 2){
        this->maxThreads = 2;
    }
    else if(maxThreads > 100){
        this->maxThreads = 100;
    }
    else{
        this->maxThreads = maxThreads;
    }
}

bool ThreadAccountant::addThread(){
    if(threadsInUse < maxThreads){
        threadsInUse ++;
        return true;
    }
    return false;
}

bool ThreadAccountant::removeThread(){
    if(threadsInUse > 0){
        threadsInUse --;
        return true;
    }
    return false;
}

int ThreadAccountant::getMaxThreadCount(){
    return maxThreads;
}

int ThreadAccountant::getThreadsInUseCount(){
    return threadsInUse;
}
