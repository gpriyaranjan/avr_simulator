#ifndef ATMEGASIM_SIM_DECODER_H
#define ATMEGASIM_SIM_DECODER_H

#include "../infra/types.h"
#include "instrn_enum.h"

class Environ;

class Decoder {
public:
    static void decode(
        const Environ& env, const TwentyTwoBit& pc,
        InstrnEnum& instrn, uchar_t& instrn_size);

};


#endif //ATMEGASIM_SIM_DECODER_H
