#ifndef ATMEGASIM_ENVIRONMENT_H
#define ATMEGASIM_ENVIRONMENT_H

#include <strings.h>
#include "types.h"

#include "status_reg.h"
#include "regs_mems.h"

constexpr uint32_t MEMORY_SIZE = 1 << 26;
constexpr uchar_t NUM_REGISTERS = 1 << 5;

class Environ {
private:
    uchar_t mem[MEMORY_SIZE];

public:
    SReg sReg;
    CPUAddr PC;

    Environ() : sReg(mem[M::SREG]) {
        PC = 0;
        bzero(this->mem, sizeof(this->mem));
    }

    void init() {
        PC = 0;
        bzero(this->mem, sizeof(this->mem));
    }

    uchar_t read_memory(CPUAddr addr);
    void write_memory(CPUAddr addr, uchar_t value);

    uchar_t read_register(FiveBit regAddr);
    void write_register(FiveBit regAddr, uchar_t value);

    uint16_t read_reg_pair(FiveBit regAddr);
};

inline uchar_t Environ::read_memory(CPUAddr addr) {
    if (addr >= MEMORY_SIZE)
        throw IllegalAddress(addr, PC);
    return mem[addr];
}

inline void Environ::write_memory(CPUAddr addr, uchar_t value) {
    if (addr >= MEMORY_SIZE)
        throw IllegalAddress(addr, PC);
    mem[addr] = value;
}

inline uchar_t Environ::read_register(FiveBit regAddr) {
    if (regAddr >= NUM_REGISTERS)
        throw IllegalAddress(regAddr, PC);
    return mem[regAddr];
}

inline uint16_t Environ::read_reg_pair(FiveBit regAddr) {
    return make_word( read_register(regAddr+1), read_register(regAddr) );
}

inline void Environ::write_register(FiveBit regAddr, uchar_t value) {
    if (regAddr >= NUM_REGISTERS)
        throw IllegalRegister(regAddr, PC);
    mem[regAddr] = value;
}

#endif //ATMEGASIM_ENVIRONMENT_H
