/*
 * SmartPointer.h
 *
 */

#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "smartpointer/RefCounter.h"
#include "smartpointer/NullPointerException.h"


/**
 * Template class to represent smart pointers (like std::shared_ptr)
 */
template<class T>
class SmartPointer {
public:
    /**
     * Constructor
     *
     * Constructs a new smart pointer from a raw pointer, sets the reference
     * counter to 1.
     *
     * @param p is a raw pointer to the object to be shared
     */
    SmartPointer(T * const p = nullptr);

    /**
     * Copy constructor
     *
     * Constructs a new smart pointer from another smart pointer, increments the
     * reference counter.
     *
     * @param p is another smart pointer
     */
    SmartPointer(const SmartPointer& p);

    /**
     * Destructor
     *
     * Decrements the reference counter. If it reaches zero, the shared object will
     * be free'd.
     */
    virtual ~SmartPointer();

    /**
     * Dereferences the smart pointer
     *
     * @return a pointer to the shared object
     */
    T *operator->() const;

    /**
     * Dereferences the smart pointer
     *
     * @return a reference to the shared object
     */
    T &operator*() const;

    /**
     * Assignment
     *
     * Changes the shared object, thus we need first to do the same
     * like the destructor, then something like the constructor.
     *
     * @param p raw pointer to the new object
     */
    const SmartPointer &operator=(T * const p);

    /**
     * Assignment
     *
     * Changes the shared object, thus we need first to do the same
     * like the destructor, then something like the copy constructor.
     *
     * @param p is another smart pointer
     */
    const SmartPointer &operator=(const SmartPointer& p);

    /**
     * Comparison
     *
     * @return true, if `p` shares the same object
     */
    bool operator==(const SmartPointer& p) const;

    /**
     * Comparison
     *
     * @return true, if `p` does not shares the same object
     */
    bool operator!=(const SmartPointer& p) const;

    /**
     * Boolean context
     *
     * @return true, if we have a shared object; false otherwise
     */
    operator bool() const;

    /**
     * Object instance
     *
     * @return raw pointer to object instance, nullptr if invalid
     */
    T* getObject() const;

    /** 
     * Reference counter
     *
     * @return reference to the refcounter
     */
    RefCounter* getRefCounter() const;
private:
    T* pObj;            ///< Pointer to the current shared object
    RefCounter *rc;     ///< Pointer to the reference counter (used for the current object)

    void release();
};

template <class T>
SmartPointer<T>::SmartPointer(T *const p) : pObj(p) {
    if (p != nullptr) {
        rc = new RefCounter();
        rc->inc();
    } else {
        rc = nullptr;
    }
}

template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer &p) : pObj(p.pObj), rc(p.rc) {
    if (rc != nullptr) {
        rc->inc();
    }
}

template <class T>
SmartPointer<T>::~SmartPointer() {
    release();
}

template <class T>
T *SmartPointer<T>::operator->() const {
    if (pObj != nullptr) {
        return pObj;
    } else {
        throw NullPointerException();
    }
}

template <class T>
T &SmartPointer<T>::operator*() const {
    if (pObj != nullptr) {
        return *pObj;
    } else {
        throw NullPointerException();
    }
}

template <class T>
const SmartPointer<T> &SmartPointer<T>::operator=(T *const p) {
    if (pObj != p) {
        release();
        pObj = p;
        rc = nullptr;
        if (pObj != nullptr) {
            rc = new RefCounter();
            rc->inc();
        }
    }
    return *this;
}

template <class T>
const SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer &p) {
    if (this != &p) {
        release();
        pObj = p.pObj;
        rc = p.rc;
        if (rc != nullptr) {
            rc->inc();
        }
    }
    return *this;
}

template <class T>
bool SmartPointer<T>::operator==(const SmartPointer &p) const {
    return pObj == p.pObj;
}

template <class T>
bool SmartPointer<T>::operator!=(const SmartPointer &p) const {
    return pObj != p.pObj;
}

template <class T>
SmartPointer<T>::operator bool() const {
    return rc != nullptr;
}

template <class T>
T* SmartPointer<T>::getObject() const {
    return pObj;
}

template <class T>
RefCounter *SmartPointer<T>::getRefCounter() const {
    return rc;
}

template <class T>
void SmartPointer<T>::release() {
    if (rc != nullptr) {
        rc->dec();
        if (rc->isZero()) {
            delete pObj;
            delete rc;
        }
    }
}

#endif  // SMARTPOINTER_H

