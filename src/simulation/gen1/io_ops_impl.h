//
// Created by MAC BOOK on 28/08/23.
//

#ifndef ATMEGASIM_SRC_IO_OPS_MC_H
#define ATMEGASIM_SRC_IO_OPS_MC_H


#include "../infra/environment.h"
#include "../infra/types.h"
#include <cstdint>

class IoOpsImpl {

public:

    static bool IN(Environ& env, FiveBit tgtAddr, SixBit srcIoAddr);
    static bool OUT(Environ& env, FiveBit srcAddr, SixBit tgtIoAddr);

    static bool SBI(Environ& env, FiveBit tgtIoPort, ThreeBit bitNum);
    static bool CBI(Environ& env, FiveBit tgtIoPort, ThreeBit bitNum);

    static void SEI(Environ& env);
    static void CLI(Environ& env);
};


#endif //ATMEGASIM_SRC_IO_OPS_MC_H
