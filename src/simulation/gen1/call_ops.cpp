#include "../decoder.h"
#include "../environment.h"
#include "branch_ops.h"
#include "call_ops.h"
#include "call_ops_impl.h"

bool CallOps::RJMP(Environ &env, ShortInstrn instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    return CallOpsImpl::RJMP(env, offset);
}

bool CallOps::JMP(Environ &env, LongInstrn instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    return CallOpsImpl::JMP(env, jmpAddr);
}

bool CallOps::IJMP(Environ &env) {
    return CallOpsImpl::IJMP(env);
}

bool CallOps::EIJMP(Environ &env) {
    return CallOpsImpl::EIJMP(env);
}

bool CallOps::PUSH(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return CallOpsImpl::PUSH(env, regAddr);
}

bool CallOps::POP(Environ &env, ShortInstrn instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return CallOpsImpl::POP(env, regAddr);
}

bool CallOps::RCALL(Environ &env, ShortInstrn instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    return CallOpsImpl::RCALL(env, offset);
}

bool CallOps::CALL(Environ &env, LongInstrn instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    return CallOpsImpl::CALL(env, jmpAddr);
}

bool CallOps::ICALL(Environ &env) {
    return CallOpsImpl::ICALL(env);
}

bool CallOps::EICALL(Environ &env) {
    return CallOpsImpl::EICALL(env);
}

bool CallOps::RET(Environ &env) {
    return CallOpsImpl::RET(env);
}

bool CallOps::RETI(Environ &env) {
    return CallOpsImpl::RETI(env);
}

