#ifndef ATMEGASIM_SRC_BRANCH_OPS_H
#define ATMEGASIM_SRC_BRANCH_OPS_H

#include "instructions.h"
#include "environment.h"

class BranchOps {
public:

    static bool CPSE(Environ& env, uint32_t instrn, InstrnEnum nextInstrn);
    static bool CPSE(Environ& env, FiveBit reg1Addr, FiveBit reg2Addr, InstrnEnum nextInstrn);

    static bool SBRC(Environ& env, uint32_t instrn, InstrnEnum nextInstrn);
    static bool SBRC(Environ& env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static bool SBRS(Environ& env, uint32_t instrn, InstrnEnum nextInstrn);
    static bool SBRS(Environ& env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static bool SBIC(Environ& env, uint32_t instrn, InstrnEnum nextInstrn);
    static bool SBIC(Environ& env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static bool SBIS(Environ& env, uint32_t instrn, InstrnEnum nextInstrn);
    static bool SBIS(Environ& env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

private:
    static bool SkipNextInstrn(Environ& env, bool skip, InstrnEnum nextInstrn);

public:

    static bool BRBS(Environ& env, uint32_t instrn);
    static bool BRBS(Environ& env, SevenBit offset, ThreeBit regBit);

private:
    static bool BranchIf(Environ& env, bool toBranch, CPUAddr addr);
};


#endif //ATMEGASIM_SRC_BRANCH_OPS_H
