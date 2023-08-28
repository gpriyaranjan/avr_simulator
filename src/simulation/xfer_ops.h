#ifndef ATMEGASIM_SRC_XFER_OPS_H
#define ATMEGASIM_SRC_XFER_OPS_H

#include "environment.h"

class XferOps {
public:

    static bool MOV(Environ& env, ShortInstrn instrn);

    static bool MOVW(Environ& env, ShortInstrn instrn);

    static bool LDI(Environ& env, ShortInstrn instrn);

    static bool LD(Environ& env, ShortInstrn instrn);

    static bool LDD(Environ& env, ShortInstrn instrn);

    static bool STS(Environ& env, LongInstrn instrn);

    static bool ST(Environ& env, ShortInstrn instrn);

    static bool STD(Environ& env, ShortInstrn instrn);

    static bool LPM(Environ& env, ShortInstrn instrn);

    static bool ELPM(Environ& env, ShortInstrn instrn);

    static bool SPM(Environ& env, ShortInstrn instrn);

    static bool XCH(Environ& env, ShortInstrn instrn);

    static bool LAS(Environ& env, ShortInstrn instrn);

    static bool LAC(Environ& env, ShortInstrn instrn);

    static bool LAT(Environ& env, ShortInstrn instrn);

};


#endif //ATMEGASIM_SRC_XFER_OPS_H
