#include "smartpointer/RefCounter.h"

RefCounter::RefCounter() {
    this->n = 0;
}

void RefCounter::inc() {
    this->n++;
}

void RefCounter::dec() {
    this->n--;
}

bool RefCounter::isZero() const {
    return this->n == 0;
}

unsigned int RefCounter::getRefCount() const {
    return this->n;
}
