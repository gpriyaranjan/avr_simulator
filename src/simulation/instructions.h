#ifndef ATMEGASIM_SRC_INSTRUCTIONS_H
#define ATMEGASIM_SRC_INSTRUCTIONS_H

enum InstrnEnum {

    // ALU Instructions
    ADD,
    ADC,
    ADIW,
    SUB,
    SBC,
    SUBI,
    SBCI,
    SBIW,
    NEG,

    INC,
    DEC,
    ASR,

    MUL,
    MULS,
    MULSU,

    FMUL,
    FMULS,
    FMULSU,

    // Comparison Group
    TST,
    CP,
    CPC,
    CPI,

    // Logical instructions
    AND,
    ANDI,
    OR,
    ORI,
    EOR,
    COM,
    SBR,
    CBR,
    SER,
    CLR,
    LSL,
    LSR,
    ROL,
    ROR,

    // Flags instructions
    BSET,
    BCLR,

    SEC,
    CLC,
    SEN,
    CLN,
    SEZ,
    CLZ,
    SEV,
    CLV,
    SES,
    CLS,
    SEH,
    CLH,
    SET,
    CLT,

    BST,
    BLD,

    // Jump and Call
    RJMP,
    JMP,
    IJMP,
    EIJMP,

    RCALL,
    CALL,
    ICALL,
    EICALL,

    RET,
    RETI,

    PUSH,
    POP,

    // Skip Group
    CPSE,
    SBRC,
    SBRS,
    SBIC,
    SBIS,

    // Branch Group
    BRBS,
    BRBC,
    BREQ,
    BRNE,
    BRCS,

    BRCC,
    BRSH,
    BRLO,
    BRMI,
    BRPL,
    BRGE,
    BRLT,
    BRVS,
    BRVC,
    BRHS,
    BRHC,
    BRTS,
    BRTC,
    BRIE,
    BRID,

    // Data xfer group
    MOV,
    MOVW,

    LDI,
    LDS,
    LD,
    LDD,

    STS,
    ST,
    STD,

    LPM,
    ELPM,
    SPM,

    // Devices and interrupt
    IN,
    OUT,
    SBI,
    CBI,
    SEI,
    CLI,

    // Atomic Instructions
    XCH,
    LAS,
    LAC,
    LAT,

    // Miscellaneous
    DES,
    BREAK,
    NOP,
    SLEEP,
    WDR
};

bool isLongInstrn(InstrnEnum instrnEnum) {
    switch(instrnEnum) {
        case InstrnEnum::JMP:
        case InstrnEnum::CALL:
        case InstrnEnum::LDS:
        case InstrnEnum::STS:
            return true;
        default:
            return false;
    }
}

#endif //ATMEGASIM_SRC_INSTRUCTIONS_H
