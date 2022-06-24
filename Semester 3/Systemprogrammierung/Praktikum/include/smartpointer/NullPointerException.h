#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include <stdexcept>

class NullPointerException : public std::runtime_error {
 public:
     NullPointerException() : std::runtime_error("aa"){}
};

#endif
