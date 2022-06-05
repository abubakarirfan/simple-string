// COS30008, Tutorial 10, 2022

#pragma once
#include <stdexcept>


template<class T>
struct Handle
{
private:
    T* fPointer;
    size_t* fCount;
    void addRef()
    {
        ++*fCount;
    }
    void releaseRef()
    {
        if (--*fCount == 0)
        {
            delete fPointer;
            delete fCount;
        }
    }
public:

    Handle(T* aPointer = nullptr)
    {
        fPointer = aPointer;
        fCount = new size_t;
        *fCount = 1;
    }

    Handle(const Handle<T>& aOtherHandle)
    {
        fPointer = aOtherHandle.fPointer;
        fCount = aOtherHandle.fCount;
        addRef();
    }

    Handle& operator=(Handle<T>& aOtherHandle)
    {
        if (&aOtherHandle != this)
        {
            aOtherHandle.addRef();
            releaseRef();
            fPointer = aOtherHandle.fPointer;
            fCount = aOtherHandle.fCount;
        }
        return *this;
    }
    ~Handle()
    {
        releaseRef();
    }
    T& operator*()
    {
        if (fPointer)
            return *fPointer;
        else
            throw std::runtime_error("Deference of unbound handle!");
    }

    T* operator->()
    {
        if (fPointer)
            return fPointer;
        else
            throw std::runtime_error("Access through unbound handle!");
    }
};
