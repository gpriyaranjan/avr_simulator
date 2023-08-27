#ifndef ATMEGASIM_SRC_SIM_GEN_H
#define ATMEGASIM_SRC_SIM_GEN_H

#include "instrn_info.h"

ISInfo instrnInfo[] = {

    ISInfo().S("ADD").T("Add without Carry")
        .P("0000-11rd-dddd-rrrr"),
    ISInfo().S("ADC").T("Add with Carry")
        .P("0001-11rd-dddd-rrrr"),
    ISInfo().S("ADIW").T("Add Immediate to Word")
        .P("1001-0110-KKdd-KKKK"),

    ISInfo().S("SUB").T("Subtract without Carry")
        .P("0001-10rd-dddd-rrrr"),
    ISInfo().S("SBC").T("Subtract with Carry")
        .P("0001-10rd-dddd-rrrr"),
    ISInfo().S("SUBI").T("Subtract Immediate without Carry")
        .P("0101-KKKK-dddd-KKKK"),
    ISInfo().S("SBCI").T("Subtract Immediate with Carry")
        .P("0100-KKKK-dddd-KKKK"),
    ISInfo().S("SBIW").T("Subtract Immediate to Word")
        .P("1001-0111-KKdd-KKKK"),

    ISInfo().S("NEG").T("Negate the Number")
        .P("1001-010d-dddd-0001"),
    ISInfo().S("INC").T("Increment byte")
        .P("1001-010d-dddd-0011"),
    ISInfo().S("DEC").T("Decrement byte")
        .P("1001-010d-dddd-0010"),
    ISInfo().S("ASR").T("Arithmetic Shift Right")
        .P("1001-010d-dddd-0101"),

    ISInfo().S("MUL").T("Multiply Unsigned")
        .P("1001-11rd-dddd-rrrr"),
    ISInfo().S("MULS").T("Multiply Signed")
        .P("0000-0010-dddd-rrrr"),
    ISInfo().S("MULSU").T("Multiply Signed Unsigned"),
    ISInfo().S("MULSU").T("Multiply Signed Unsigned"),

    ISInfo().S("FMUL").T("Fractional Multiply Unsigned"),
    ISInfo().S("FMULS").T("Fractional Multiply Signed"),
    ISInfo().S("FMULSU").T("Fractional Multiply Signed Unsigned"),
    ISInfo().S("FMULSU").T("Fractional Multiply Signed Unsigned"),

    ISInfo().S("TST").T("Test for zero or minus"),
    ISInfo().S("CP").T("Compare if Equal"),
    ISInfo().S("CPC").T("Compare with Carry"),
    ISInfo().S("CPI").T("Compare with Immediate")
};

#endif //ATMEGASIM_SRC_SIM_GEN_H
