#include "decoder.h"
#include "environment.h"
#include "branch_ops.h"
#include "call_ops.h"

bool CallOps::RJMP(Environ &env, uint32_t instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    return RJMP(env, offset, true);
}

bool CallOps::RJMP(Environ &env, TwelveBit tgtOffset, bool dummy) {
    uint16_t offset1 = tgtOffset - (1 << 11);
    env.PC = env.PC + offset1;
    return true;
}

bool CallOps::JMP(Environ &env, uint64_t instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    return JMP(env, jmpAddr, false);
}

bool CallOps::JMP(Environ &env, TwentyTwoBit jmpAddr, bool dummy) {
    env.PC = jmpAddr;
    return true;
}

bool CallOps::IJMP(Environ &env) {
    return IJMP(env, true);
}

bool CallOps::IJMP(Environ &env, bool dummy) {
    env.PC = env.read_reg_pair(M::Z);
    return true;
}

bool CallOps::EIJMP(Environ &env) {
    return EIJMP(env, true);
}

bool CallOps::EIJMP(Environ &env, bool dummy) {
    env.PC = env.read_reg_pair(M::Z);
    env.PC |= (env.read_mem_byte(M::EIND) & 0x3F) << 24;
    return true;
}

bool CallOps::PUSH(Environ &env, uint32_t instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return PUSH(env, regAddr, true);
}

bool CallOps::PUSH(Environ &env, FiveBit regAddr, bool dummy) {
    uchar_t value = env.read_reg_byte(regAddr);
    Push1Byte(env, value);
    return false;
}

bool CallOps::POP(Environ &env, uint32_t instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    return POP(env, regAddr, true);
}

bool CallOps::POP(Environ &env, FiveBit regAddr, bool dummy) {
    uchar_t value;
    Pop1Byte(env, value);
    env.write_reg_byte(regAddr, value);
    return false;
}

bool CallOps::RCALL(Environ &env, uint32_t instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    return RCALL(env, offset, true);
}

bool CallOps::RCALL(Environ &env, TwelveBit tgtOffset, bool dummy) {
    uchar_t instrnSize = 4 + isLongInstrn(InstrnEnum::RCALL);
    uint32_t retAddr = env.PC + instrnSize;
    Push3Bytes(env, retAddr);
    return RJMP(env, tgtOffset, dummy);
}

bool CallOps::CALL(Environ &env, uint64_t instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    return CALL(env, jmpAddr, false);
}

bool CallOps::CALL(Environ &env, TwentyTwoBit tgtOffset, bool dummy) {
    uchar_t instrnSize = 4 + isLongInstrn(InstrnEnum::CALL);
    uint32_t retAddr = env.PC + instrnSize;
    Push3Bytes(env, retAddr);
    return JMP(env, tgtOffset, dummy);
}

bool CallOps::ICALL(Environ &env) {
    return ICALL(env, true);
}

bool CallOps::ICALL(Environ &env, bool dummy) {
    uchar_t instrnSize = 4 + isLongInstrn(InstrnEnum::ICALL);
    uint32_t retAddr = env.PC + instrnSize;
    Push3Bytes(env, retAddr);
    return IJMP(env, dummy);
}

bool CallOps::EICALL(Environ &env) {
    return EICALL(env, true);
}

bool CallOps::EICALL(Environ &env, bool dummy) {
    uchar_t instrnSize = 4 + isLongInstrn(InstrnEnum::EICALL);
    uint32_t retAddr = env.PC + instrnSize;
    Push3Bytes(env, retAddr);
    return EIJMP(env, dummy);
}

bool CallOps::RET(Environ &env) {
    return RET(env, true);
}

bool CallOps::RET(Environ &env, bool dummy) {
    TwentyTwoBit pcValue;
    Pop3Bytes(env, pcValue);
    env.PC = pcValue;
    return true;
}

bool CallOps::RETI(Environ &env) {
    return RETI(env, true);
}

bool CallOps::RETI(Environ &env, bool dummy) {
    TwentyTwoBit pcValue;
    Pop3Bytes(env, pcValue);
    env.PC = pcValue;
}

void CallOps::Push1Byte(Environ& env, uchar_t value) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    env.write_mem_byte(stackPtr, value);
    stackPtr--;
    env.write_reg_pair(M::SP, stackPtr);
}

void CallOps::Pop1Byte(Environ &env, uchar_t &value) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    stackPtr++;
    value = env.read_mem_byte(stackPtr);
}

void CallOps::Push3Bytes(Environ &env, TwentyTwoBit pcValue) {
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

void CallOps::Pop3Bytes(Environ &env, TwentyTwoBit& pcValue) {
    uint16_t stackPtr = env.read_reg_pair(M::SP);
    uchar_t value;
    for(int i = 0; i < 2; i++) {
        value = env.read_mem_byte(stackPtr);
        pcValue = (pcValue << 8) | value;
    }
    env.write_reg_pair(M::SP, stackPtr);
}
