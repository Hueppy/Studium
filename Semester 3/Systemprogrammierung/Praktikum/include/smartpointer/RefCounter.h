/*
 * RefCounter.h
 *
 */

#ifndef REFCOUNTER_H
#define REFCOUNTER_H


/**
 * Auxiliary class for counting the references (interface)
 */
class RefCounter {
public:

    /**
     * Default constructor
     */
    RefCounter();

    /**
     * Increment count
     */
    void inc();

    /**
     * Decrement count
     */
    void dec();

    /**
     * Compare the counter with zero
     *
     * @return true if n==0, false otherwise
     */
    bool isZero() const;

    /**
     * Returns count
     *
     * @return n
     */
    unsigned int getRefCount() const;

    // Hide copy constructor and assignment operator
    RefCounter(const RefCounter&) = delete;
    RefCounter &operator=(const RefCounter&) = delete;

private:
    unsigned int n;     ///< How many SmartPointer share ownership of "our" object?
};


#endif /* REFCOUNTER_H */
