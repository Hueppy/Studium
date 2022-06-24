#include "smartpointer/SmartPointerImpl.h"
#include "smartpointer/NullPointerException.h"

#include <iostream>

int main()
{
    int *x = new int;
    SmartPointer<int> p(x);

    p = x;

    std::cout << p.getObject() << "\n";
    std::cout << p.getRefCounter() << "\n";
    
    return 0;
}
