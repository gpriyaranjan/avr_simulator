#ifndef ATMEGASIM_ENVIRONMENT_H
#define ATMEGASIM_ENVIRONMENT_H

#include <strings.h>
#include "simple_utils.h"

typedef struct SReg_ {
    bool C: 1; // Carry flag
    bool Z: 1; // Zero flag
    bool N: 1; // Negative flag
    bool V: 1; // Overflow flag
    bool S: 1; // Signed flag
    bool H: 1; // Half carry flag
    bool T: 1; // T flag
    bool I: 1; // I flag

public:
    SReg_() {
        C = Z = N = V = S = H = T = I = false;
    }

    void init() {
        C = Z = N = V = S = H = T = I = false;
    }

    SReg_& setC(bool c) { C = c; return *this; }
    SReg_& setZ(bool z) { Z = z; return *this; }
    SReg_& setN(bool n) { N = n; return *this; }
    SReg_& setV(bool v) { V = v; return *this; }
    SReg_& setS(bool s) { S = s; return *this; }
    SReg_& setH(bool h) { H = h; return *this; }
    SReg_& setT(bool t) { T = t; return *this; }
    SReg_& setI(bool i) { I = i; return *this; }

    SReg_& setS() { S = N^V; return *this; }

} __attribute__((packed)) SReg;

#define CBit 0
#define ZBit 1
#define NBit 2
#define VBit 3
#define SBit 4
#define HBit 5
#define TBit 6
#define IBit 7

#define CMask 1<<CBit
#define ZMask 1<<ZBit
#define NMask 1<<NBit
#define VMask 1<<VBit
#define SMask 1<<SBit
#define HMask 1<<HBit
#define TMask 1<<TBit
#define IMask 1<<IBit

class Environ {
public:
    UChar mem[1L << 32];
    SReg sReg;
    short PC;

    Environ() {
        PC = 0;
        bzero(this->mem, 1L << 32);
    }

    void init() {
        PC = 0;
        bzero(this->mem, 1L << 32);
        sReg.init();
    }
};

#endif //ATMEGASIM_ENVIRONMENT_H
