#include <cstdint>
#include "../types.h"
#include "../gen1/call_ops.h"
#include "../gen1/branch_ops.h"
#include "../environment.h"
#include "../instructions.h"
#include "../gen1/call_ops_impl.h"

class CallOpsImplP {

public:

    static void Push1Byte(Environ& env, uchar_t value);
    static void Pop1Byte(Environ& env, uchar_t& value);

    static void Push3Bytes(Environ& env, TwentyTwoBit pcValue);
    static void Pop3Bytes(Environ& env, TwentyTwoBit& pcValue);
};

bool CallOpsImpl::RJMP(Environ &env, TwelveBit tgtOffset) {
    uint16_t offset1 = tgtOffset - (1 << 11);
    env.PC = env.PC + offset1;
    return true;
}

bool CallOpsImpl::JMP(Environ &env, TwentyTwoBit jmpAddr) {
    env.PC = jmpAddr;
    return true;
}

bool CallOpsImpl::IJMP(Environ &env) {
    env.PC = env.read_reg_pair(M::Z);
    return true;
}

bool CallOpsImpl::EIJMP(Environ &env) {
    env.PC = env.read_reg_pair(M::Z);
    env.PC |= (env.read_mem_byte(M::EIND) & 0x3F) << 24;
    return true;
}

bool CallOpsImpl::PUSH(Environ &env, FiveBit regAddr) {
    uchar_t value = env.read_reg_byte(regAddr);
    CallOpsImplP::Push1Byte(env, value);
    return false;
}

bool CallOpsImpl::POP(Environ &env, FiveBit regAddr) {
    uchar_t value;
    CallOpsImplP::Pop1Byte(env, value);
    env.write_reg_byte(regAddr, value);
    return false;
}

bool CallOpsImpl::RCALL(Environ &env, TwelveBit tgtOffset) {
    uchar_t instrnSize = isLongInstrn(InstrnEnum::RCALL) ? 2 : 3;
    uint32_t retAddr = env.PC + instrnSize;
    CallOpsImplP::Push3Bytes(env, retAddr);
    return RJMP(env, tgtOffset);
}

bool CallOpsImpl::CALL(Environ &env, TwentyTwoBit tgtAddr) {
    uchar_t instrnSize = isLongInstrn(InstrnEnum::CALL) ? 2 : 3;
    uint32_t retAddr = env.PC + instrnSize;
    CallOpsImplP::Push3Bytes(env, retAddr);
    return JMP(env, tgtAddr);
}

bool CallOpsImpl::ICALL(Environ &env) {
    uchar_t instrnSize = isLongInstrn(InstrnEnum::ICALL) ? 2 : 3;
    uint32_t retAddr = env.PC + instrnSize;
    CallOpsImplP::Push3Bytes(env, retAddr);
    return IJMP(env);
}

bool CallOpsImpl::EICALL(Environ &env) {
    uchar_t instrnSize = isLongInstrn(InstrnEnum::EICALL) ? 2 : 3;
    uint32_t retAddr = env.PC + instrnSize;
    CallOpsImplP::Push3Bytes(env, retAddr);
    return EIJMP(env);
}

bool CallOpsImpl::RET(Environ &env) {
    TwentyTwoBit pcValue;
    CallOpsImplP::Pop3Bytes(env, pcValue);
    env.PC = pcValue;
    return true;
}

bool CallOpsImpl::RETI(Environ &env) {
    TwentyTwoBit pcValue;
    CallOpsImplP::Pop3Bytes(env, pcValue);
    env.PC = pcValue;
    return true;
}

void CallOpsImplP::Push1Byte(Environ& env, uchar_t value) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    env.write_mem_byte(stackPtr, value);
    stackPtr--;
    env.write_reg_pair(M::SP, stackPtr);
}

void CallOpsImplP::Pop1Byte(Environ &env, uchar_t &value) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    stackPtr++;
    value = env.read_mem_byte(stackPtr);
}

void CallOpsImplP::Push3Bytes(Environ &env, TwentyTwoBit pcValue) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    uchar_t value;
    for(int i = 0; i < 2; i++) {
        value = pcValue & 0xFF;
        env.write_mem_byte(stackPtr, value);
        stackPtr--;
        pcValue = pcValue >> 8;
    }
    env.write_reg_pair(M::SP, stackPtr);
}

void CallOpsImplP::Pop3Bytes(Environ &env, TwentyTwoBit& pcValue) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    uchar_t value;
    for(int i = 0; i < 2; i++) {
        value = env.read_mem_byte(stackPtr);
        pcValue = (pcValue << 8) | value;
    }
    env.write_reg_pair(M::SP, stackPtr);
}