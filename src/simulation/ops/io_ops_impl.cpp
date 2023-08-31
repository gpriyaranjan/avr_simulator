#include "../infra/environment.h"
#include "../gen2/io_ops_impl.h"

void IoOpsImpl::IN(Environ &env, FiveBit tgtRegNum, SixBit portAddr) {
    // Todo : Implement this in a meaningful way
}

void IoOpsImpl::OUT(Environ &env, FiveBit srcRegNum, SixBit portAddr) {
    // Todo : Implement this in a meaningful way
}

void IoOpsImpl::SBI(Environ &env, FiveBit portAddr, ThreeBit bitNum) {
    // Todo : Implement this in a meaningful way
}

void IoOpsImpl::CBI(Environ &env, FiveBit portAddr, ThreeBit bitNum) {
    // Todo : Implement this in a meaningful way
}

void IoOpsImpl::SEI(Environ &env) {
    env.sReg.setI(true);
}

void IoOpsImpl::CLI(Environ &env) {
    env.sReg.setI(false);
}
