#ifndef ATMEGASIM_SRC_STATUS_REG_H
#define ATMEGASIM_SRC_STATUS_REG_H

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

enum SBits {
    CBit = 0,
    ZBit = 1,
    NBit = 2,
    VBit = 3,
    SBit = 4,
    HBit = 5,
    TBit = 6,
    IBit = 7
};

enum SMasks {
    CMask = 1<<CBit,
    ZMask = 1<<ZBit,
    NMask = 1<<NBit,
    VMask = 1<<VBit,
    SMask = 1<<SBit,
    HMask = 1<<HBit,
    TMask = 1<<TBit,
    IMask = 1<<IBit
};

#endif //ATMEGASIM_SRC_STATUS_REG_H
