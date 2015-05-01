#ifndef SP_H
#define SP_H

#include "referencecounter.h"
//class ReferenceCounter;

template < typename T > class SP
{
public:
    //all the different constructors
    SP();
    SP(T* pValue);
    SP(T* pValue, ReferenceCounter * rc);
    SP(const SP<T>& sp);

    //cast
    template<typename TCast> SP<TCast> castTo(){
        TCast* data = (TCast*)this->pData;
        return SP<TCast>(data, this->refCount);
    }

    //very dangerous!
    //reinterpret cast
    template<typename TCast> SP<TCast> reinterpretCastTo(){
        TCast* data = reinterpret_cast<TCast*>(this->pData);
        return SP<TCast>(data, this->refCount);
    }

    //dynamic cast
    template<typename TCast> SP<TCast> dynamicCastTo(){
        TCast* data = dynamic_cast<TCast*>(this->pData);
        if(data != nullptr)
            return SP<TCast>(data, this->refCount);
        else
            return SP<TCast>(data, new ReferenceCounter());
    }


    //destructor...
    ~SP();


    T* getPointer();

    //Dereferencing operator
    T& operator* ();

    //Indirection operator
    T* operator-> ();

    //the copy operator
    SP<T>& operator = (const SP<T>& sp);

    //the compair operators
    bool operator ==(const SP<T>& sp);
    bool operator ==(const T* t_data);

    bool operator !=(const SP<T>& sp);
    bool operator !=(const T* t_data);

private:
    T*    pData;                    // pointer to Data
    ReferenceCounter* refCount;    // Reference count
};

#endif // SP_H
