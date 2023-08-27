#ifndef ATMEGASIM_SRC_BRANCH_OPS_H
#define ATMEGASIM_SRC_BRANCH_OPS_H

#include "environment.h"

class BranchOps {
public:

    static void CPSE(Environ& env, uint32_t instrn);
    static void CPSE(Environ& env, FiveBit& reg1Addr, FiveBit& reg2Addr);

};


#endif //ATMEGASIM_SRC_BRANCH_OPS_H
