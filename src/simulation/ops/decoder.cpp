#include "decoder.h"

InstrnEnum Decoder::decode(ShortInstrn instrn) {

    switch(instrn & 0xc000) {
        case 0x8000: return STD;
        default: break;
    };

    switch(instrn & 0xf000) {
        case 0xe000: return LDI;
        case 0x7000: return CBR;
        case 0x6000: return SBR;
        case 0xc000: return RJMP;
        case 0xd000: return RCALL;
        case 0x5000: return SUBI;
        case 0x4000: return SBCI;
        case 0x3000: return CPI;
        default: break;
    };

    switch(instrn & 0xf800) {
        case 0xb000: return IN;
        case 0xb800: return OUT;
        default: break;
    };

    switch(instrn & 0xfc00) {
        case 0x2c00: return MOV;
        case 0x2000: return TST;
        case 0x2800: return OR;
        case 0x2400: return CLR;
        case 0xc00: return ADD;
        case 0x1c00: return ADC;
        case 0x1000: return CPSE;
        case 0xf000: return BRIE;
        case 0xf400: return BRID;
        case 0x1800: return SBC;
        case 0x9c00: return MUL;
        case 0x1400: return CP;
        case 0x400: return CPC;
        default: break;
    };

    switch(instrn & 0xfe00) {
        case 0x9000: return POP;
        case 0x8000: return ST;
        case 0x9200: return PUSH;
        case 0x9400: return ASR;
        case 0xfc00: return SBRC;
        case 0xfe00: return SBRS;
        case 0xfa00: return BST;
        case 0xf800: return BLD;
        default: break;
    };

    switch(instrn & 0xff00) {
        case 0x100: return MOVW;
        case 0xef00: return SER;
        case 0x9b00: return SBIC;
        case 0x9900: return SBIS;
        case 0x9600: return ADIW;
        case 0x9700: return SBIW;
        case 0x200: return MULS;
        case 0x9a00: return SBI;
        case 0x9800: return CBI;
        default: break;
    };

    switch(instrn & 0xff80) {
        case 0x9400: return BSET;
        case 0x9480: return BCLR;
        case 0x300: return FMUL;
        case 0x380: return FMULSU;
        default: break;
    };

    switch(instrn & 0xffe0) {
        case 0x95e0: return SPM;
        default: break;
    };

    switch(instrn & 0xffff) {
        case 0x9409: return IJMP;
        case 0x9419: return EIJMP;
        case 0x9509: return ICALL;
        case 0x9519: return EICALL;
        case 0x9508: return RET;
        case 0x9518: return RETI;
        case 0x9408: return SEC;
        case 0x9488: return CLC;
        case 0x9428: return SEN;
        case 0x94a8: return CLN;
        case 0x9418: return SEZ;
        case 0x9498: return CLZ;
        case 0x9438: return SEV;
        case 0x94b8: return CLV;
        case 0x9448: return SES;
        case 0x94c8: return CLS;
        case 0x9458: return SEH;
        case 0x94d8: return CLH;
        case 0x9468: return SET;
        case 0x94e8: return CLT;
        case 0x9478: return SEI;
        case 0x94f8: return CLI;
        default: break;
    };

    return NOP;
}
