#include <cstdint>
#include "../infra/types.h"
#include "../gen2/call_ops.h"
#include "../gen2/branch_ops.h"
#include "../infra/environment.h"
#include "../gen2/instrns.h"
#include "../gen2/call_ops_impl.h"

class CallOpsImplP {

public:

    static void Push1Byte(Environ& env, uchar_t value);
    static void Pop1Byte(Environ& env, uchar_t& value);

    static void Push3Bytes(Environ& env, TwentyTwoBit pcValue);
    static void Pop3Bytes(Environ& env, TwentyTwoBit& pcValue);
};

void CallOpsImpl::RJMP(Environ &env, TwelveBit tgtOffset) {
    uint16_t offset1 = tgtOffset - (1 << 11);
    env.CU.setRJump(offset1);
}

void CallOpsImpl::JMP(Environ &env, TwentyTwoBit jmpAddr) {
    env.CU.setJump(jmpAddr);
}

void CallOpsImpl::IJMP(Environ &env) {
    SixteenBit jmpAddr = env.read_reg_pair(M::Z);
    env.CU.setJump(jmpAddr);
}

void CallOpsImpl::EIJMP(Environ &env) {
    SixteenBit jmpAddr;
    jmpAddr = env.read_reg_pair(M::Z);
    jmpAddr |= (env.read_mem_byte(M::EIND) & 0x3F) << 24;
    env.CU.setJump(jmpAddr);
}

void CallOpsImpl::PUSH(Environ &env, FiveBit regAddr) {
    uchar_t value = env.read_reg_byte(regAddr);
    CallOpsImplP::Push1Byte(env, value);
}

void CallOpsImpl::POP(Environ &env, FiveBit regAddr) {
    uchar_t value;
    CallOpsImplP::Pop1Byte(env, value);
    env.write_reg_byte(regAddr, value);
}

void CallOpsImpl::RCALL(Environ &env, TwelveBit tgtOffset) {
    uint32_t retAddr = env.CU.getNextPC();
    CallOpsImplP::Push3Bytes(env, retAddr);
    RJMP(env, tgtOffset);
}

void CallOpsImpl::CALL(Environ &env, TwentyTwoBit tgtAddr) {
    uint32_t retAddr = env.CU.getNextPC();
    CallOpsImplP::Push3Bytes(env, retAddr);
    JMP(env, tgtAddr);
}

void CallOpsImpl::ICALL(Environ &env) {
    uint32_t retAddr = env.CU.getNextPC();
    CallOpsImplP::Push3Bytes(env, retAddr);
    IJMP(env);
}

void CallOpsImpl::EICALL(Environ &env) {
    uint32_t retAddr = env.CU.getNextPC();
    CallOpsImplP::Push3Bytes(env, retAddr);
    EIJMP(env);
}

void CallOpsImpl::RET(Environ &env) {
    TwentyTwoBit pcValue;
    CallOpsImplP::Pop3Bytes(env, pcValue);
    env.CU.setJump(pcValue);
}

void CallOpsImpl::RETI(Environ &env) {
    TwentyTwoBit pcValue;
    CallOpsImplP::Pop3Bytes(env, pcValue);
    env.CU.setJump(pcValue);
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