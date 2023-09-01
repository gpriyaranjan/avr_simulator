#ifndef ATMEGASIM_ENVIRONMENT_H
#define ATMEGASIM_ENVIRONMENT_H

#include <strings.h>
#include "types.h"
#include "exceptions.h"

#include "status_reg.h"
#include "regs_mems.h"
#include "control_unit.h"

constexpr uint32_t MEMORY_SIZE = 1 << 26;
constexpr uchar_t NUM_REGISTERS = 1 << 5;

class Environ {
private:
    uchar_t mem[MEMORY_SIZE];

public:
    SReg sReg;
    ControlUnit CU;

    Environ() : sReg(mem[M::SREG]), CU(*this) {
        bzero(this->mem, sizeof(this->mem));
    }

    void init() {
        bzero(this->mem, sizeof(this->mem));
    }

    [[nodiscard]] uchar_t read_mem_byte(CPUAddr addr) const;
    void write_mem_byte(CPUAddr addr, uchar_t value);

    uchar_t read_reg_byte(FiveBit regAddr);
    void write_reg_byte(FiveBit regAddr, uchar_t value);

    [[nodiscard]] uint16_t read_mem_pair(CPUAddr addr) const;
    void write_mem_pair(CPUAddr addr, uint16_t value);

    uint16_t read_reg_pair(FiveBit regAddr);
    void write_reg_pair(FiveBit regAddr, uint16_t value);

};

inline uchar_t Environ::read_mem_byte(CPUAddr addr) const {
    if (addr >= MEMORY_SIZE)
        throw IllegalAddress(addr, CU.getCurrPC());
    return mem[addr];
}

inline void Environ::write_mem_byte(CPUAddr addr, uchar_t value) {
    if (addr >= MEMORY_SIZE)
        throw IllegalAddress(addr, CU.getCurrPC());
    mem[addr] = value;
}

inline uchar_t Environ::read_reg_byte(FiveBit regAddr) {
    if (regAddr >= NUM_REGISTERS)
        throw IllegalAddress(regAddr, CU.getCurrPC());
    return mem[regAddr];
}

inline uint16_t Environ::read_reg_pair(FiveBit regAddr) {
    return make_word(read_reg_byte(regAddr + 1), read_reg_byte(regAddr) );
}

inline uint16_t Environ::read_mem_pair(CPUAddr memAddr) const {
    return make_word(read_mem_byte(memAddr + 1), read_mem_byte(memAddr) );
}

inline void Environ::write_reg_byte(FiveBit regAddr, uchar_t value) {
    if (regAddr >= NUM_REGISTERS)
        throw IllegalRegister(regAddr, CU.getCurrPC());
    mem[regAddr] = value;
}

void Environ::write_reg_pair(FiveBit regAddr, uint16_t value) {
    write_reg_byte(regAddr, lo_byte(value));
    write_reg_byte(regAddr, hi_byte(value));
}

inline void Environ::write_mem_pair(CPUAddr memAddr, uint16_t value) {
    write_mem_byte(memAddr, lo_byte(value));
    write_mem_byte(memAddr, hi_byte(value));
}

inline void decode(
    const Environ &env, const TwentyTwoBit &pc, InstrnEnum &instrn, uchar_t &instrn_size) {

    ShortInstrn word = env.read_mem_pair(pc);
    instrn = decode(instrn);
}

#endif //ATMEGASIM_ENVIRONMENT_H
