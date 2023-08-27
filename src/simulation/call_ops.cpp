#include "decoder.h"
#include "environment.h"
#include "branch_ops.h"
#include "call_ops.h"

void CallOps::RJMP(Environ &env, uint32_t instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    RJMP(env, offset, true);
}

void CallOps::RJMP(Environ &env, TwelveBit tgtOffset, bool dummy) {
    uint16_t offset1 = tgtOffset - (1 << 11);
    env.PC = env.PC + offset1;
}

void CallOps::JMP(Environ &env, uint64_t instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    JMP(env, jmpAddr, false);
}

void CallOps::JMP(Environ &env, TwentyTwoBit jmpAddr, bool dummy) {
    env.PC = jmpAddr;
}

void CallOps::IJMP(Environ &env) {
    IJMP(env, true);
}

void CallOps::IJMP(Environ &env, bool dummy) {
    env.PC = env.read_reg_pair(M::Z);
}

void CallOps::EIJMP(Environ &env) {
    EIJMP(env, true);
}

void CallOps::EIJMP(Environ &env, bool dummy) {
    env.PC = env.read_reg_pair(M::Z);
    env.PC |= (env.read_mem_byte(M::EIND) & 0x3F) << 24;
}

void CallOps::PUSH(Environ &env, uint32_t instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    PUSH(env, regAddr, true);
}

void CallOps::PUSH(Environ &env, FiveBit regAddr, bool dummy) {
    uchar_t value = env.read_reg_byte(regAddr);
    Push1Byte(env, value);
}

void CallOps::POP(Environ &env, uint32_t instrn) {
    FiveBit regAddr;
    ArgsDecode::Reg5(instrn, regAddr);
    POP(env, regAddr, true);
}

void CallOps::POP(Environ &env, FiveBit regAddr, bool dummy) {
    uchar_t value;
    Pop1Byte(env, value);
    env.write_reg_byte(regAddr, value);
}

void CallOps::RCALL(Environ &env, uint32_t instrn) {
    TwelveBit offset;
    ArgsDecode::Addr12(instrn, offset);
    RCALL(env, offset, true);
}

void CallOps::RCALL(Environ &env, TwelveBit tgtOffset, bool dummy) {
    Push3Bytes(env, env.PC);
    RJMP(env, tgtOffset, dummy);
}

void CallOps::CALL(Environ &env, uint64_t instrn) {
    TwentyTwoBit jmpAddr;
    ArgsDecode::Addr22(instrn, jmpAddr);
    CALL(env, jmpAddr, false);
}

void CallOps::CALL(Environ &env, TwentyTwoBit tgtOffset, bool dummy) {
    Push3Bytes(env, env.PC);
    JMP(env, tgtOffset, dummy);
}

void CallOps::ICALL(Environ &env) {
    ICALL(env, true);
}

void CallOps::ICALL(Environ &env, bool dummy) {
    Push3Bytes(env, env.PC);
    IJMP(env, dummy);
}

void CallOps::EICALL(Environ &env) {
    EICALL(env, true);
}

void CallOps::EICALL(Environ &env, bool dummy) {
    Push3Bytes(env, env.PC);
    EIJMP(env, dummy);
}

void CallOps::RET(Environ &env) {
    RET(env, true);
}

void CallOps::RET(Environ &env, bool dummy) {
    TwentyTwoBit pcValue;
    Pop3Bytes(env, pcValue);
    env.PC = pcValue;
}

void CallOps::RETI(Environ &env) {
    RETI(env, true);
}

void CallOps::RETI(Environ &env, bool dummy) {
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
