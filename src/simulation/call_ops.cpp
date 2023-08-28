#include "decoder.h"
#include "environment.h"
#include "branch_ops.h"
#include "call_ops.h"
#include "call_ops_mc.h"

bool CallOps::RJMP(Environ &env, ShortInstrn instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    return CallOpsMc::RJMP(env, offset);
}

bool CallOps::JMP(Environ &env, LongInstrn instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    return CallOpsMc::JMP(env, jmpAddr);
}

bool CallOps::IJMP(Environ &env) {
    return CallOpsMc::IJMP(env);
}

bool CallOps::EIJMP(Environ &env) {
    return CallOpsMc::EIJMP(env);
}

bool CallOps::PUSH(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return CallOpsMc::PUSH(env, regAddr);
}

bool CallOps::POP(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return CallOpsMc::POP(env, regAddr);
}

bool CallOps::RCALL(Environ &env, ShortInstrn instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    return CallOpsMc::RCALL(env, offset);
}

bool CallOps::CALL(Environ &env, LongInstrn instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    return CallOpsMc::CALL(env, jmpAddr);
}

bool CallOps::ICALL(Environ &env) {
    return CallOpsMc::ICALL(env);
}

bool CallOps::EICALL(Environ &env) {
    return CallOpsMc::EICALL(env);
}

bool CallOps::RET(Environ &env) {
    return CallOpsMc::RET(env);
}

bool CallOps::RETI(Environ &env) {
    return CallOpsMc::RETI(env);
}

