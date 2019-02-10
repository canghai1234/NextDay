#ifndef SINGLETON_H
#define SINGLETON_H

#include <QAtomicPointer>

template<typename T>
class Singleton
{
public:
    static T* getSingleton()
    {
        if (!sInstancePtr.loadAcquire())
        {
            T* ptr = new T();
            if (!sInstancePtr.testAndSetOrdered(0, ptr))
                delete ptr;
        }
        return sInstancePtr.loadAcquire();
    }

    static void release()
    {
        T* ptr = sInstancePtr.loadAcquire();
        if (ptr)
            if (sInstancePtr.testAndSetOrdered(ptr, 0))
                delete ptr;
    }

protected:
    Singleton(){}
    virtual ~Singleton(){}

private:
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);

    static QBasicAtomicPointer<T> sInstancePtr;
};

template<typename T>
QBasicAtomicPointer<T> Singleton<T>::sInstancePtr = Q_BASIC_ATOMIC_INITIALIZER(0);

#endif // SINGLETON_H
