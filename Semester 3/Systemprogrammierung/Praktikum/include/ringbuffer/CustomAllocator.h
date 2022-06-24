/*
 * CustomAllocator.h
 *
 */

#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <iostream>

/**
 * Template classo to represent a custom allocator, to be used via `std::allocator_traits`
 *
 * @param T is the type to be allocated/deallocated
 */
template <class T>
class CustomAllocator {
public:
    /**
     * Type trait to access type T
     */
    typedef T value_type;

    /**
     * Default constructor
     */
    CustomAllocator() {}

    /**
     * Copy constructor
     */
    template <class U> constexpr CustomAllocator (const CustomAllocator <U>&) noexcept {}

    /**
     * Allocates $n$ elements of type T and returns a pointer to the first element
     *
     * @param n is the number of elements to be allocated
     * @return pointer to the first element
     */
    T* allocate(size_t n);

    /**
     * Free's $n$ elements of type T that were allocated with this allocator using `allocate(n)`
     *
     * @param p is a pointer to the element (or to the first of several elements) to be free'd
     * @param n is the number of elements used in `allocate`
     */
    void deallocate(T* p, size_t n) noexcept;
};

/// Comparison of allocators
template <class T, class U>
bool operator==(const CustomAllocator <T>&, const CustomAllocator <U>&) { return true; }
template <class T, class U>
bool operator!=(const CustomAllocator <T>&, const CustomAllocator <U>&) { return false; }


#ifdef NOPALLOC

template <class T> T *CustomAllocator<T>::allocate(size_t n) {
    throw std::bad_alloc();
}

template <class T>
void CustomAllocator<T>::deallocate(T* p, size_t n) noexcept {
}

#else
#ifdef CM_MALLOC

#include "speicherverwaltung/speicherverwaltung.h"

template <class T> T *CustomAllocator<T>::allocate(size_t n) {
    T *result = (T *)cm_malloc(sizeof(value_type) * n);
    std::cout << "Allocated " << n << " (" << result << " - "
              << result + n - 1 << ")\n";

    return result;
}

template <class T>
void CustomAllocator<T>::deallocate(T* p, size_t n) noexcept {
    std::cout << "Dellocating " << n << " bytes (" << p << " - "
              << p + n - 1 << ")\n";
    cm_free(p);
}

#else

#include <cstdlib>

template <class T>
T* CustomAllocator<T>::allocate(size_t n) {
    T *result = (T *)malloc(sizeof(value_type) * n);
    std::cout << "Allocated " << n << " (" << result << " - "
               << result + n - 1 << ")\n";

    return result;
}

template <class T>
void CustomAllocator<T>::deallocate(T* p, size_t n) noexcept {
    std::cout << "Dellocating " << n << " bytes (" << p << " - "
              << p + n - 1 << ")\n";
    free(p);
}

#endif
#endif

#endif  // CUSTOMALLOCATOR_H
