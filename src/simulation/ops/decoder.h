#ifndef ATMEGASIM_SIM_DECODER_H
#define ATMEGASIM_SIM_DECODER_H

#include "../infra/types.h"
#include "../infra/environment.h"
#include "../gen2/instrn_enum.h"

class Decoder {
public:
    static InstrnEnum decode(ShortInstrn instrn);

};


#endif //ATMEGASIM_SIM_DECODER_H
