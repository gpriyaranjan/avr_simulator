#ifndef ATMEGASIM_ALUOPS_H
#define ATMEGASIM_ALUOPS_H

#include <cstdint>
#include "../infra/types.h"
#include "../infra/environment.h"

class AluOps {
public:

    static bool ADD(Environ& env, ShortInstrn instrn);
    static bool ADC(Environ& env, ShortInstrn instrn);
    static bool ADIW(Environ& env, ShortInstrn instrn);

    static bool SUB(Environ& env, ShortInstrn instrn);
    static bool SBC(Environ& env, ShortInstrn instrn);
    static bool SUBI(Environ& env, ShortInstrn instrn);
    static bool SBCI(Environ& env, ShortInstrn instrn);
    static bool SBIW(Environ& env, ShortInstrn instrn);
    static bool NEG(Environ& env, ShortInstrn instrn);

    static bool INC(Environ& env, ShortInstrn instrn);
    static bool DEC(Environ& env, ShortInstrn instrn);
    static bool ASR(Environ& env, ShortInstrn instrn);

    static bool MUL(Environ& env, ShortInstrn instrn);
    static bool MULS(Environ& env, ShortInstrn instrn);
    static bool MULSU(Environ& env, ShortInstrn instrn);

    static bool FMUL(Environ& env, ShortInstrn instrn);
    static bool FMULS(Environ& env, ShortInstrn instrn);
    static bool FMULSU(Environ& env, ShortInstrn instrn);

    static bool TST(Environ& env, ShortInstrn instrn);
    static bool CP(Environ& env, ShortInstrn instrn);
    static bool CPC(Environ& env, ShortInstrn instrn);
    static bool CPI(Environ& env, ShortInstrn instrn);

};


#endif //ATMEGASIM_ALUOPS_H
