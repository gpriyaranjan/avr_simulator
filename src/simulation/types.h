#ifndef ATMEGASIM_TYPES_H
#define ATMEGASIM_TYPES_H

# include <cstdint>
#include <exception>

#define bi(byte,i) ((byte & 0x01)>>i)

#define is_bi(byte, i) (bi(byte, i) == 1)
#define is_b0(byte) is_bi(byte,0)
#define is_b3(byte) is_bi(byte,3)
#define is_b7(byte) is_bi(byte,7)

#define is_nbi(byte, i) (bi(byte, i) == 0)
#define is_nb0(byte) is_nbi(byte,0)
#define is_nb3(byte) is_nbi(byte,3)
#define is_nb7(byte) is_nbi(byte,7)

#define is_zero(byte) (byte == 0)

typedef unsigned char OneBit;
typedef unsigned char TwoBit;
typedef unsigned char ThreeBit;
typedef unsigned char FourBit;
typedef unsigned char FiveBit;
typedef unsigned char SixBit;
typedef unsigned char SevenBit;
typedef unsigned char EightBit;

typedef unsigned char uchar_t;
typedef   signed char schar_t;

typedef uint16_t TwelveBit;
typedef uint32_t TwentyTwoBit;
typedef uint32_t TwentySixBit;

typedef TwentySixBit CPUAddr;

inline uchar_t lo_byte(uint16_t src) {return src & 0xFF;}
inline uchar_t hi_byte(uint16_t src) {return src >> 8;}

inline uint16_t make_word(uchar_t hi_byte, uchar_t lo_byte) {
    return (hi_byte>>8) | lo_byte;
}

class IllegalAddress : public std::exception {
public:
    CPUAddr addr;
    CPUAddr pc;
    IllegalAddress(CPUAddr addr_, CPUAddr pc_)
        : addr(addr_), pc(pc_) {}
};

class IllegalRegister : public std::exception {
public:
    FiveBit addr;
    CPUAddr pc;
    IllegalRegister(FiveBit addr_, CPUAddr pc_)
    : addr(addr_), pc(pc_) {}
};

#endif //ATMEGASIM_TYPES_H
