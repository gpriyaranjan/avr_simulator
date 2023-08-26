#ifndef ATMEGASIM_SRC_BRANCH_OPS_H
#define ATMEGASIM_SRC_BRANCH_OPS_H

#include "environment.h"

class BranchOps {
public:

    static void RJMP(Environ& env, unsigned int instrn);

};


#endif //ATMEGASIM_SRC_BRANCH_OPS_H
