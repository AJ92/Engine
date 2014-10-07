#ifndef REFERENCECOUNTER_H
#define REFERENCECOUNTER_H

class ReferenceCounter
{

public:
    ReferenceCounter();

    void AddRef();
    int Release();

private:
    int refCount; // Reference count
};

#endif // REFERENCECOUNTER_H
