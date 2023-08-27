#ifndef ATMEGASIM_SRC_BRANCH_OPS_H
#define ATMEGASIM_SRC_BRANCH_OPS_H

#include "instructions.h"
#include "environment.h"

class BranchOps {
public:

    static bool CPSE(Environ& env, uint32_t instrn, bool nextInstrnLong);
    static bool CPSE(Environ& env, FiveBit& reg1Addr, FiveBit& reg2Addr, bool nextInstrnLong);

};


#endif //ATMEGASIM_SRC_BRANCH_OPS_H
