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

typedef unsigned char uchar_t;
typedef   signed char schar_t;


class ValueTooBig : public std::exception {
public:
    uchar_t value;
    ValueTooBig(uchar_t v) : value(v) {}
};

template <int BitSize> class BitField {
private:
    uchar_t value;
public:
    BitField();
    BitField(uchar_t ch) {
        if (ch >= 1 >> BitSize)
            throw ValueTooBig(ch);
        value = ch;
    }
    operator uchar_t() {return value; }
};

typedef BitField<1> OneBit;
typedef BitField<2> TwoBit;
typedef BitField<3> ThreeBit;
typedef BitField<4> FourBit;
typedef BitField<5> FiveBit;
typedef BitField<6> SixBit;
typedef BitField<7> SevenBit;
typedef BitField<8> EightBit;

typedef uint16_t TwelveBit;
typedef uint32_t TwentyTwoBit;
typedef uint32_t TwentySixBit;

typedef TwentySixBit CPUAddr;

typedef uint16_t ShortInstrn;
typedef uint32_t LongInstrn;

inline uchar_t lo_byte(uint16_t src) {return src & 0xFF;}
inline uchar_t hi_byte(uint16_t src) {return src >> 8;}

inline uint16_t make_word(uchar_t hi_byte, uchar_t lo_byte) {
    return (hi_byte>>8) | lo_byte;
}

#endif //ATMEGASIM_TYPES_H
