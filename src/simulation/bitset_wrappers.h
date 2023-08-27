#ifndef ATMEGASIM_SRC_BITSET_WRAPPERS_H
#define ATMEGASIM_SRC_BITSET_WRAPPERS_H

/*
#include <iostream>
#include <string>

template<class T, int Sz>
class BitsetWrapper {
    T value;
public:
    typedef T value_type;
    bool isValid(T value) {
        if ((value > 0) && value >= (1 << Sz))
            throw ValueTooBig()
    }
    BitsetWrapper() : value() {}
    BitsetWrapper(T v) : value(v) {}
    operator T() const {return value;}
    //modifiers
    BitsetWrapper& operator=(T v) { value=v; return *this;}
    BitsetWrapper& operator+=(T v) { value+=v; return *this;}
    BitsetWrapper& operator-=(T v) { value-=v; return *this;}
    BitsetWrapper& operator*=(T v) { value*=value; return *this;}
    BitsetWrapper& operator/=(T v) { value/=value; return *this;}
    BitsetWrapper& operator%=(T v) { value%=value; return *this;}
    BitsetWrapper& operator++() {++value; return *this;}
    BitsetWrapper& operator--() {--value; return *this;}
    BitsetWrapper operator++(int) {return BitsetWrapper(value++);}
    BitsetWrapper operator--(int) {return BitsetWrapper(value--);}
    BitsetWrapper& operator&=(T v) { value&=v; return *this;}
    BitsetWrapper& operator|=(T v) { value|=v; return *this;}
    BitsetWrapper& operator^=(T v) { value^=v; return *this;}
    BitsetWrapper& operator<<=(T v) { value<<=v; return *this;}
    BitsetWrapper& operator>>=(T v) { value>>=v; return *this;}
    //accessors
    BitsetWrapper operator+() const {return BitsetWrapper(+value);}
    BitsetWrapper operator-() const {return BitsetWrapper(-value);}
    BitsetWrapper operator!() const {return BitsetWrapper(!value);}
    BitsetWrapper operator~() const {return BitsetWrapper(~value);}
    //friends
    friend BitsetWrapper operator+(BitsetWrapper iw, BitsetWrapper v) {return iw+=v;}
    friend BitsetWrapper operator+(BitsetWrapper iw, T v) {return iw+=v;}
    friend BitsetWrapper operator+(T v, BitsetWrapper iw) {return BitsetWrapper(v)+=iw;}
    friend BitsetWrapper operator-(BitsetWrapper iw, BitsetWrapper v) {return iw-=v;}
    friend BitsetWrapper operator-(BitsetWrapper iw, T v) {return iw-=v;}
    friend BitsetWrapper operator-(T v, BitsetWrapper iw) {return BitsetWrapper(v)-=iw;}
    friend BitsetWrapper operator*(BitsetWrapper iw, BitsetWrapper v) {return iw*=v;}
    friend BitsetWrapper operator*(BitsetWrapper iw, T v) {return iw*=v;}
    friend BitsetWrapper operator*(T v, BitsetWrapper iw) {return BitsetWrapper(v)*=iw;}
    friend BitsetWrapper operator/(BitsetWrapper iw, BitsetWrapper v) {return iw/=v;}
    friend BitsetWrapper operator/(BitsetWrapper iw, T v) {return iw/=v;}
    friend BitsetWrapper operator/(T v, BitsetWrapper iw) {return BitsetWrapper(v)/=iw;}
    friend BitsetWrapper operator%(BitsetWrapper iw, BitsetWrapper v) {return iw%=v;}
    friend BitsetWrapper operator%(BitsetWrapper iw, T v) {return iw%=v;}
    friend BitsetWrapper operator%(T v, BitsetWrapper iw) {return BitsetWrapper(v)%=iw;}
    friend BitsetWrapper operator&(BitsetWrapper iw, BitsetWrapper v) {return iw&=v;}
    friend BitsetWrapper operator&(BitsetWrapper iw, T v) {return iw&=v;}
    friend BitsetWrapper operator&(T v, BitsetWrapper iw) {return BitsetWrapper(v)&=iw;}
    friend BitsetWrapper operator|(BitsetWrapper iw, BitsetWrapper v) {return iw|=v;}
    friend BitsetWrapper operator|(BitsetWrapper iw, T v) {return iw|=v;}
    friend BitsetWrapper operator|(T v, BitsetWrapper iw) {return BitsetWrapper(v)|=iw;}
    friend BitsetWrapper operator^(BitsetWrapper iw, BitsetWrapper v) {return iw^=v;}
    friend BitsetWrapper operator^(BitsetWrapper iw, T v) {return iw^=v;}
    friend BitsetWrapper operator^(T v, BitsetWrapper iw) {return BitsetWrapper(v)^=iw;}
    friend BitsetWrapper operator<<(BitsetWrapper iw, BitsetWrapper v) {return iw<<=v;}
    friend BitsetWrapper operator<<(BitsetWrapper iw, T v) {return iw<<=v;}
    friend BitsetWrapper operator<<(T v, BitsetWrapper iw) {return BitsetWrapper(v)<<=iw;}
    friend BitsetWrapper operator>>(BitsetWrapper iw, BitsetWrapper v) {return iw>>=v;}
    friend BitsetWrapper operator>>(BitsetWrapper iw, T v) {return iw>>=v;}
    friend BitsetWrapper operator>>(T v, BitsetWrapper iw) {return BitsetWrapper(v)>>=iw;}
};
typedef intWrapperImpl<int> intWrapper;
typedef intWrapperImpl<unsigned> uintWrapper;
typedef intWrapperImpl<short> shortWrapper;
typedef intWrapperImpl<char> charWrapper;
typedef intWrapperImpl<unsigned long long> ullWrapper;
*/

#endif //ATMEGASIM_SRC_BITSET_WRAPPERS_H
