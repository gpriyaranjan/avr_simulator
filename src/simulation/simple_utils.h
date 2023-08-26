#ifndef ATMEGASIM_TESTS_SIMPLE_UTILS_H
#define ATMEGASIM_TESTS_SIMPLE_UTILS_H

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

typedef unsigned char UChar;
typedef   signed char SChar;

// typedef uint32_t  FourBytes;
typedef uint64_t EightBytes;

#endif //ATMEGASIM_TESTS_SIMPLE_UTILS_H
