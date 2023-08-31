#include "io_ops.h"
#include "../infra/decoder.h"
#include "sreg_ops.h"

bool IoOps::IN(Environ &env, ShortInstrn instrn) {
    FiveBit tgtRegAddr; SixBit ioPort;
    ArgsDecode::Reg5IO6(instrn, tgtRegAddr, ioPort);
    return IN(env, tgtRegAddr, ioPort);
}

bool IoOps::IN(Environ &env, FiveBit tgtRegAddr, SixBit srcIoAddr) {
    // Todo : Do something meaningful here
    return false;
}

bool IoOps::OUT(Environ &env, ShortInstrn instrn) {
    FiveBit tgtRegAddr; SixBit ioPort;
    ArgsDecode::Reg5IO6(instrn, tgtRegAddr, ioPort);
    return false;
}

bool IoOps::OUT(Environ &env, FiveBit srcAddr, SixBit tgtIoAddr) {
    // Todo : Attach to devices here
    return false;
}

bool IoOps::SBI(Environ &env, ShortInstrn instrn) {
    FiveBit ioPort; ThreeBit bitNum;
    ArgsDecode::IO5Bit3(instrn, ioPort, bitNum);
    return SBI(env, ioPort, bitNum);
}

bool IoOps::SBI(Environ &env, FiveBit tgtIoPort, ThreeBit bitNum) {
    // Todo : Attach to devices here
    return false;
}

bool IoOps::CBI(Environ &env, ShortInstrn instrn) {
    FiveBit ioPort; ThreeBit bitNum;
    ArgsDecode::IO5Bit3(instrn, ioPort, bitNum);
    return CBI(env, ioPort, bitNum);
}

bool IoOps::CBI(Environ &env, FiveBit tgtIoPort, ThreeBit bitNum) {
    // Todo : Attach to devices here
    return false;
}

bool IoOps::SEI(Environ &env, ShortInstrn instrn) {
    return SEI(env);
}

bool IoOps::SEI(Environ &env) {
    return SRegOps::BSET(env, IBit);
}

bool IoOps::CLI(Environ &env, ShortInstrn instrn) {
    return CLI(env);
}

bool IoOps::CLI(Environ &env) {
    return SRegOps::BCLR(env, IBit);
}

