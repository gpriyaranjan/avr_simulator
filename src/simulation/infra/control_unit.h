#ifndef ATMEGASIM_SIM_CONTROL_UNIT_H
#define ATMEGASIM_SIM_CONTROL_UNIT_H

#include "types.h"
#include "../gen2/instrns.h"

class Environ;
inline void decode(
    const Environ &env, const TwentyTwoBit &pc, InstrnEnum &instrn, uchar_t &instrn_size);

struct PCStatus {
    uchar_t L: 1; // Current instuction length
    uchar_t J: 1; // Jump flag - PC has been set to next instrn
    uchar_t S: 1; // Skip flag - Skip the next instruction
};

class ControlUnit {
private:
    const Environ& env;
    CPUAddr PC;
    InstrnEnum currInstrn;
    PCStatus pcStatus;

public:

    ControlUnit(const Environ& env_) : env(env_) {
        PC = 0;
        pcStatus.J = false;
        pcStatus.S = false;
    }

    void resetFlags() {
        pcStatus.J = false;
        pcStatus.S = false;
    }

    [[nodiscard]] TwentyTwoBit getCurrPC() const {
        return PC & 0x3FFF;
    }

    TwentyTwoBit getNextPC() {
        return PC & 0x3FFF + pcStatus.L;
    }
    void setSkipNext(bool status=true) {
        pcStatus.S = status;
    }

    void setJump(TwentyTwoBit nextPC, bool status=true) {
        pcStatus.J = status;
        PC = nextPC;
    }

    void setRJump(TwentyTwoBit nextPC, bool status=true) {
        pcStatus.J = status;
        PC = PC + nextPC;
    }

    InstrnEnum stepPC() {
        uchar_t instrn_size;

        if (pcStatus.J) {
            decode(env, PC, currInstrn, instrn_size);
            pcStatus.L = instrn_size;
            return currInstrn;
        }

        PC = PC + pcStatus.L;

        if (pcStatus.S) {
            decode(env, PC, currInstrn, instrn_size);
            PC += instrn_size;
        }

        decode(env, PC, currInstrn, instrn_size);
        pcStatus.L = instrn_size;
        resetFlags();
        return currInstrn;
    }

};

#endif //ATMEGASIM_SIM_CONTROL_UNIT_H
