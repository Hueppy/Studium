//============================================================================
// Name        : IteratorContainer.cpp
// Author      : Carsten Gips
// Description : Beispiel fuer eigene Iteratoren und Container
//============================================================================

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>

using namespace std;


template<typename T>
class MyIterator : public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T *, T &> {
public:
    MyIterator(T *ptr = nullptr) : m_ptr(ptr) { }

    MyIterator(const MyIterator<T> &) = default;

    virtual ~MyIterator() = default;

    MyIterator<T> &operator=(const MyIterator<T> &) = default;

    MyIterator<T> &operator=(T *ptr) {
        m_ptr = ptr;
        return *this;
    }

    operator bool() const {
        if (m_ptr)
            return true;
        else
            return false;
    }

    bool operator==(const MyIterator<T> &o) const {
        return (m_ptr == o.getConstPtr());
    }

    bool operator!=(const MyIterator<T> &o) const {
        return !(*this == o);
    }

    MyIterator<T> &operator+=(const ptrdiff_t &offset) {
        m_ptr += offset;
        return *this;
    }

    MyIterator<T> &operator-=(const ptrdiff_t &offset) {
        m_ptr -= offset;
        return *this;
    }

    MyIterator<T> &operator++() {
        ++m_ptr;
        return *this;
    }

    MyIterator<T> &operator--() {
        --m_ptr;
        return *this;
    }

    MyIterator<T> operator++(int) {
        MyIterator<T> temp(*this);
        ++m_ptr;
        return temp;
    }

    MyIterator<T> operator--(int) {
        MyIterator<T> temp(*this);
        --m_ptr;
        return temp;
    }

    MyIterator<T> operator+(const ptrdiff_t &offset) {
        MyIterator<T> temp(*this);
        temp += offset;
        return temp;
    }

    MyIterator<T> operator-(const ptrdiff_t &offset) {
        MyIterator<T> temp(*this);
        temp -= offset;
        return temp;
    }

    ptrdiff_t operator-(const MyIterator<T> &other) {
        return std::distance(other.getPtr(), this->getPtr());
    }

    T &operator*() {
        return *m_ptr;
    }

    const T &operator*() const {
        return *m_ptr;
    }

    T *operator->() {
        return m_ptr;
    }

    T *getPtr() const {
        return m_ptr;
    }

    const T *getConstPtr() const {
        return m_ptr;
    }

protected:
    T *m_ptr;
};


template<typename T, int N>
class MyContainer {
public:
    MyContainer(initializer_list <T> v) {
        typename initializer_list<T>::const_iterator it = v.begin();

        for (int i = 0; i < N; ++i) {
            if (it != v.end()) {
                m_data[i] = *it;
                ++it;
            } else {
                m_data[i] = 0;
            }
        }
    }

    typedef MyIterator<T> iterator;
    typedef MyIterator<const T> const_iterator;

    iterator begin() {
        return iterator(&m_data[0]);
    }

    iterator end() {
        return iterator(&m_data[m_size]);
    }

    const_iterator cbegin() {
        return const_iterator(&m_data[0]);
    }

    const_iterator cend() {
        return const_iterator(&m_data[m_size]);
    }

private:
    int m_size = N;
    T m_data[N];
};


int main() {
    MyContainer<int, 10> c = {1, 2, 3, 4};
    MyContainer<int, 10>::const_iterator i;

    for (i = c.cbegin(); i != c.cend(); i++) {
        cout << "i: " << *i << endl;
    }

    return EXIT_SUCCESS;
}
