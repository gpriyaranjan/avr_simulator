#ifndef ATMEGASIM_SIM_DECODER_H
#define ATMEGASIM_SIM_DECODER_H

#include "../infra/types.h"
#include "../gen2/instrn_enum.h"

class Environ;

class Decoder {
public:
    static void decode(
        const Environ& env, const TwentyTwoBit& pc,
        InstrnEnum& instrn, uchar_t& instrn_size);

    static InstrnEnum decode(ShortInstrn instrn);
};


#endif //ATMEGASIM_SIM_DECODER_H
