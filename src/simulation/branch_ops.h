#ifndef ATMEGASIM_SRC_BRANCH_OPS_H
#define ATMEGASIM_SRC_BRANCH_OPS_H

#include "instructions.h"
#include "environment.h"

class BranchOps {
public:

    static bool CPSE(Environ& env, uint16_t instrn, InstrnEnum nextInstrn);
    static bool CPSE(Environ& env, FiveBit reg1Addr, FiveBit reg2Addr, InstrnEnum nextInstrn);

    static bool SBRC(Environ& env, uint16_t instrn, InstrnEnum nextInstrn);
    static bool SBRC(Environ& env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static bool SBRS(Environ& env, uint16_t instrn, InstrnEnum nextInstrn);
    static bool SBRS(Environ& env, FiveBit regAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static bool SBIC(Environ& env, uint16_t instrn, InstrnEnum nextInstrn);
    static bool SBIC(Environ& env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

    static bool SBIS(Environ& env, uint16_t instrn, InstrnEnum nextInstrn);
    static bool SBIS(Environ& env, FiveBit portAddr, ThreeBit bitNum, InstrnEnum nextInstrn);

private:
    static bool SkipNextInstrn(Environ& env, bool skip, InstrnEnum nextInstrn);

public:

    static bool BRBS(Environ& env, uint16_t instrn);
    static bool BRBS(Environ& env, SevenBit offset, ThreeBit regBit);

    static bool BRBC(Environ& env, uint16_t instrn);
    static bool BRBC(Environ& env, SevenBit offset, ThreeBit regBit);

    static bool BREQ(Environ& env, uint16_t instrn);
    static bool BREQ(Environ& env, SevenBit offset);

    static bool BRNE(Environ& env, uint16_t instrn);
    static bool BRNE(Environ& env, SevenBit offset);

    static bool BRCS(Environ& env, uint16_t instrn);
    static bool BRCS(Environ& env, SevenBit offset);

    static bool BRCC(Environ& env, uint16_t instrn);
    static bool BRCC(Environ& env, SevenBit offset);

    static bool BRLO(Environ& env, uint16_t instrn);
    static bool BRLO(Environ& env, SevenBit offset);

    static bool BRSH(Environ& env, uint16_t instrn);
    static bool BRSH(Environ& env, SevenBit offset);

    static bool BRMI(Environ& env, uint16_t instrn);
    static bool BRMI(Environ& env, SevenBit offset);

    static bool BRPL(Environ& env, uint16_t instrn);
    static bool BRPL(Environ& env, SevenBit offset);

    static bool BRVS(Environ& env, uint16_t instrn);
    static bool BRVS(Environ& env, SevenBit offset);

    static bool BRVC(Environ& env, uint16_t instrn);
    static bool BRVC(Environ& env, SevenBit offset);

    static bool BRLT(Environ& env, uint16_t instrn);
    static bool BRLT(Environ& env, SevenBit offset);

    static bool BRGE(Environ& env, uint16_t instrn);
    static bool BRGE(Environ& env, SevenBit offset);

    static bool BRHS(Environ& env, uint16_t instrn);
    static bool BRHS(Environ& env, SevenBit offset);

    static bool BRHC(Environ& env, uint16_t instrn);
    static bool BRHC(Environ& env, SevenBit offset);

    static bool BRTS(Environ& env, uint16_t instrn);
    static bool BRTS(Environ& env, SevenBit offset);

    static bool BRTC(Environ& env, uint16_t instrn);
    static bool BRTC(Environ& env, SevenBit offset);

    static bool BRIE(Environ& env, uint16_t instrn);
    static bool BRIE(Environ& env, SevenBit offset);

    static bool BRID(Environ& env, uint16_t instrn);
    static bool BRID(Environ& env, SevenBit offset);

private:
    static bool Branchif(Environ& env, bool toSkip, SevenBit offset);
};


#endif //ATMEGASIM_SRC_BRANCH_OPS_H
