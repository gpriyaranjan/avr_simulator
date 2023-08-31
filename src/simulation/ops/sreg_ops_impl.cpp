#include <cstdint>
#include "../infra/types.h"
#include "../infra/environment.h"
#include "../gen2/sreg_ops.h"
#include "../gen2/sreg_ops_impl.h"

class SregOpsImplP {
public:
    static void WriteBit(Environ& env, ThreeBit regNum);
};

void SregOpsImpl::BSET(Environ &env, ThreeBit regNum) {
    SregOpsImplP::WriteBit(env, regNum);
}

void SregOpsImpl::BCLR(Environ &env, ThreeBit regNum) {
    SregOpsImplP::WriteBit(env, regNum);
}

void SregOpsImpl::SEC(Environ &env) {
    SregOpsImpl::BSET(env, CBit);
}

void SregOpsImpl::CLC(Environ &env) {
    SregOpsImpl::BCLR(env, CBit);
}

void SregOpsImpl::SEZ(Environ &env) {
    SregOpsImpl::BSET(env, ZBit);
}

void SregOpsImpl::CLZ(Environ &env) {
    SregOpsImpl::BCLR(env, ZBit);
}

void SregOpsImpl::SEN(Environ &env) {
    SregOpsImpl::BSET(env, NBit);
}

void SregOpsImpl::CLN(Environ &env) {
    SregOpsImpl::BCLR(env, NBit);
}

void SregOpsImpl::SEV(Environ &env) {
    SregOpsImpl::BSET(env, VBit);
}

void SregOpsImpl::CLV(Environ &env) {
    SregOpsImpl::BCLR(env, VBit);
}

void SregOpsImpl::SES(Environ &env) {
    SregOpsImpl::BSET(env, SBit);
}

void SregOpsImpl::CLS(Environ &env) {
    SregOpsImpl::BCLR(env, SBit);
}

void SregOpsImpl::SEH(Environ &env) {
    SregOpsImpl::BSET(env, HBit);
}

void SregOpsImpl::CLH(Environ &env) {
    SregOpsImpl::BCLR(env, HBit);
}

void SregOpsImpl::SET(Environ &env) {
    SregOpsImpl::BSET(env, SBit);
}

void SregOpsImpl::CLT(Environ &env) {
    SregOpsImpl::BCLR(env, TBit);
}

void SregOpsImpl::BST(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_reg_byte(tgtAddr);
    bool tBit = is_bi(tgtValue, regNum);
    env.sReg.setT(tBit);
}

void SregOpsImpl::BLD(Environ &env, FiveBit tgtAddr, ThreeBit regNum) {
    uchar_t tgtValue = env.read_reg_byte(tgtAddr);
    uchar_t tBitMask = env.sReg.T() << regNum;
    uchar_t result = tgtValue | tBitMask;
    env.write_reg_byte(tgtAddr, result);
}

void SregOpsImplP::WriteBit(Environ &env, ThreeBit regNum) {

    auto regBit = (SMasks)(1 << regNum);

    switch(regBit) {
        case CMask:
            env.sReg.setC(true);
            break;
        case ZMask:
            env.sReg.setZ(true);
            break;
        case NMask:
            env.sReg.setN(true);
            break;
        case VMask:
            env.sReg.setV(true);
            break;
        case SMask:
            env.sReg.setS(true);
            break;
        case HMask:
            env.sReg.setH(true);
            break;
        case TMask:
            env.sReg.setT(true);
            break;
        case IMask:
            env.sReg.setI(true);
            break;
        default:
            break;
    }
}