#include "call_ops.h"
#include "branch_ops.h"
#include "environment.h"
#include "instructions.h"
#include "decoder.h"
#include "call_ops_mc.h"

bool CallOpsMc::RJMP(Environ &env, TwelveBit tgtOffset) {
    uint16_t offset1 = tgtOffset - (1 << 11);
    env.PC = env.PC + offset1;
    return true;
}

bool CallOpsMc::JMP(Environ &env, TwentyTwoBit jmpAddr) {
    env.PC = jmpAddr;
    return true;
}

bool CallOpsMc::IJMP(Environ &env) {
    env.PC = env.read_reg_pair(M::Z);
    return true;
}

bool CallOpsMc::EIJMP(Environ &env) {
    env.PC = env.read_reg_pair(M::Z);
    env.PC |= (env.read_mem_byte(M::EIND) & 0x3F) << 24;
    return true;
}

bool CallOpsMc::PUSH(Environ &env, FiveBit regAddr) {
    uchar_t value = env.read_reg_byte(regAddr);
    Push1Byte(env, value);
    return false;
}

bool CallOpsMc::POP(Environ &env, FiveBit regAddr) {
    uchar_t value;
    Pop1Byte(env, value);
    env.write_reg_byte(regAddr, value);
    return false;
}

bool CallOpsMc::RCALL(Environ &env, TwelveBit tgtOffset) {
    uchar_t instrnSize = isLongInstrn(InstrnEnum::RCALL) ? 2 : 3;
    uint32_t retAddr = env.PC + instrnSize;
    Push3Bytes(env, retAddr);
    return RJMP(env, tgtOffset);
}

bool CallOpsMc::CALL(Environ &env, TwentyTwoBit tgtAddr) {
    uchar_t instrnSize = isLongInstrn(InstrnEnum::CALL) ? 2 : 3;
    uint32_t retAddr = env.PC + instrnSize;
    Push3Bytes(env, retAddr);
    return JMP(env, tgtAddr);
}

bool CallOpsMc::ICALL(Environ &env) {
    uchar_t instrnSize = isLongInstrn(InstrnEnum::ICALL) ? 2 : 3;
    uint32_t retAddr = env.PC + instrnSize;
    Push3Bytes(env, retAddr);
    return IJMP(env);
}

bool CallOpsMc::EICALL(Environ &env) {
    uchar_t instrnSize = isLongInstrn(InstrnEnum::EICALL) ? 2 : 3;
    uint32_t retAddr = env.PC + instrnSize;
    Push3Bytes(env, retAddr);
    return EIJMP(env);
}

bool CallOpsMc::RET(Environ &env) {
    TwentyTwoBit pcValue;
    Pop3Bytes(env, pcValue);
    env.PC = pcValue;
    return true;
}

bool CallOpsMc::RETI(Environ &env) {
    TwentyTwoBit pcValue;
    Pop3Bytes(env, pcValue);
    env.PC = pcValue;
    return true;
}

void CallOpsMc::Push1Byte(Environ& env, uchar_t value) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    env.write_mem_byte(stackPtr, value);
    stackPtr--;
    env.write_reg_pair(M::SP, stackPtr);
}

void CallOpsMc::Pop1Byte(Environ &env, uchar_t &value) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    stackPtr++;
    value = env.read_mem_byte(stackPtr);
}

void CallOpsMc::Push3Bytes(Environ &env, TwentyTwoBit pcValue) {
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

void CallOpsMc::Pop3Bytes(Environ &env, TwentyTwoBit& pcValue) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    uchar_t value;
    for(int i = 0; i < 2; i++) {
        value = env.read_mem_byte(stackPtr);
        pcValue = (pcValue << 8) | value;
    }
    env.write_reg_pair(M::SP, stackPtr);
}