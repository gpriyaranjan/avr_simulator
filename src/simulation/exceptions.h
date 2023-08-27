#ifndef ATMEGASIM_SRC_EXCEPTIONS_H
#define ATMEGASIM_SRC_EXCEPTIONS_H

#include "types.h"

class IllegalAddress : public std::exception {
public:
    CPUAddr addr;
    CPUAddr pc;
    IllegalAddress(CPUAddr addr_, CPUAddr pc_)
        : addr(addr_), pc(pc_) {}
};

class IllegalRegister : public std::exception {
public:
    FiveBit addr;
    CPUAddr pc;
    IllegalRegister(FiveBit addr_, CPUAddr pc_)
        : addr(addr_), pc(pc_) {}
};

#endif //ATMEGASIM_SRC_EXCEPTIONS_H
