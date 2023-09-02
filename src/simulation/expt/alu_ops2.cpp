#include "../gen2/instrns.h"
#include "alu_ops2.h"

ShortInstrn AluOps2::ADD(FiveBit srcAddr, FiveBit tgtAddr) {
    ShortInstrn code = InstrnEnum::ADD;
    code = code | (srcAddr & 0x0F) | ( (srcAddr & 0x10 ) << 5 );
    code = code | ( (tgtAddr & 0x0F) << 4 );
    return code;
}
