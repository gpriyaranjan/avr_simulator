#ifndef ATMEGASIM_SIM_CONTROL_UNIT_H
#define ATMEGASIM_SIM_CONTROL_UNIT_H

#include "types.h"
#include "../ops/decoder.h"
#include "../ops/instrn_enum.h"

class Environ;

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

    TwentyTwoBit getPC() {
        return PC & 0x3FFF;
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
            Decoder::decode(env, PC, currInstrn, instrn_size);
            pcStatus.L = instrn_size;
            return currInstrn;
        }

        PC = PC + pcStatus.L;

        if (pcStatus.S) {
            Decoder::decode(env, PC, currInstrn, instrn_size);
            PC += instrn_size;
        }

        Decoder::decode(env, PC, currInstrn, instrn_size);
        pcStatus.L = instrn_size;
        resetFlags();
        return currInstrn;
    }
};

#endif //ATMEGASIM_SIM_CONTROL_UNIT_H
