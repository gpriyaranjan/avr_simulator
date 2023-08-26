#ifndef ATMEGASIM_SRC_BRANCH_OPS_H
#define ATMEGASIM_SRC_BRANCH_OPS_H

#include <cstdint>
#include "environment.h"

class BranchOps {
public:

    static void RJMP(Environ& env, uint32_t instrn);
    static void RJMP(Environ& env, TwelveBit tgtOffset, bool dummy);

    static void JMP(Environ& env, uint64_t instrn);
    static void JMP(Environ &env, TwentyTwoBit instrn, bool dummy);

    static void IJMP(Environ& env);
    static void IJMP(Environ& env, bool dummy);

};


#endif //ATMEGASIM_SRC_BRANCH_OPS_H
