#ifndef ATMEGASIM_SRC_STATUS_REG_H
#define ATMEGASIM_SRC_STATUS_REG_H

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


class SReg {
private:
    uchar_t& value;

public:
    explicit SReg(uchar_t& value_) : value(value_) {};

    [[nodiscard]] bool Z() const { return (bool)(value >> ZBit); }
    SReg setZ(bool c) { value |= (c << ZBit); return *this; }

    [[nodiscard]] bool C() const { return (bool)(value >> CBit); }
    SReg setC(bool c) { value |= (c << CBit); return *this; }

    [[nodiscard]] bool N() const { return (bool)(value >> NBit); }
    SReg setN(bool c) { value |= (c << NBit); return *this; }

    [[nodiscard]] bool V() const { return (bool)(value >> VBit); }
    SReg setV(bool c) { value |= (c << VBit); return *this; }

    [[nodiscard]] bool S() const { return (bool)(value >> SBit); }
    SReg setS(bool c) { value |= (c << SBit); return *this; }
    SReg setS() { value = N()^V(); return *this; }

    [[nodiscard]] bool H() const { return (bool)(value >> HBit); }
    SReg setH(bool c) { value |= (c << HBit); return *this; }

    [[nodiscard]] bool T() const { return (bool)(value >> TBit); }
    SReg setT(bool c) { value |= (c << TBit); return *this; }

    [[nodiscard]] bool I() const { return (bool)(value >> TBit); }
    SReg setI(bool c) { value |= (c << IBit); return *this; }

};

#endif //ATMEGASIM_SRC_STATUS_REG_H
