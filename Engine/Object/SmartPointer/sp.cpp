#include "sp.h"
#include "referencecounter.h"
#include <QString>

template<typename T>
SP<T>::SP() :
    pData(0),
    refCount(0)
{
    // Create a new reference
    refCount = new ReferenceCounter();
    // Increment the reference count
    refCount->AddRef();
}


template<typename T>
SP<T>::SP(T* pValue) :
    pData(pValue),
    refCount(0)
{
    // Create a new reference
    refCount = new ReferenceCounter();
    // Increment the reference count
    refCount->AddRef();
}

template<typename T>
SP<T>::SP(const SP<T>& sp) :
    pData(sp.pData),
    refCount(sp.refCount)
{
    refCount->AddRef();
}

//destructor...
template<typename T>
SP<T>::~SP(){
    // Destructor
    // Decrement the reference count
    // if reference Counter become zero delete the data
    int refC_rel = refCount->Release();
    if(refC_rel < 0){
        qDebug("FUCKIN OVER OR UNDERFLOW!!!");
        qDebug("SmartPointer deleted the pointer, but the pointer was used somewhere else probably...");
    }
    if(refC_rel == 0)
    {

        delete pData;
        delete refCount;
    }
}

template<typename T>
T* SP<T>::getPointer(){
    return pData;
}

//Dereferencing operator
template<typename T>
T& SP<T>::operator* (){
    return *pData;
}

//Indirection operator
template<typename T>
T* SP<T>::operator-> (){
    return pData;
}

//the copy operator
template<typename T>
SP<T>& SP<T>::operator = (const SP<T>& sp){
    // Assignment operator
    if (this != &sp) // Avoid self assignment
    {
        // Decrement the old reference count
        // if reference become zero delete the old data
        if(refCount->Release() == 0)
        {
            delete pData;
            delete refCount;
        }

        // Copy the data and reference pointer
        // and increment the reference count
        pData = sp.pData;
        refCount = sp.refCount;
        refCount->AddRef();
    }
    return *this;
}

//the compair operator
template<typename T>
bool SP<T>::operator == (const SP<T>& sp){
    if(pData == sp.pData){
        return true;
    }
    return false;
}


//the compair operator which can be used to check if the pointer
//was initialized...
template<typename T>
bool SP<T>::operator == (const T* t_data){
    if(pData == t_data){
        return true;
    }
    return false;
}



template<typename T>
bool SP<T>::operator != (const SP<T>& sp){
    if(pData != sp.pData){
        return true;
    }
    return false;
}

template<typename T>
bool SP<T>::operator != (const T* t_data){
    if(pData != t_data){
        return true;
    }
    return false;
}
