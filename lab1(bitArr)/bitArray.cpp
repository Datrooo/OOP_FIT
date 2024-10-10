#include "bitArray.h"
#include "iostream"
#include <algorithm>

const int BitArray::bitsPerBlock = sizeof(unsigned long) * BYTE;

BitArray::BitArray() : sizeOfBuf(0) {}

BitArray::~BitArray() {}    

BitArray::BitArray(int numBits, unsigned long value)
    : bits((numBits + bitsPerBlock - 1) / bitsPerBlock, 0), sizeOfBuf(numBits){
    if (numBits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative.");
    }

    int minSize = std::min(numBits, bitsPerBlock);
    for (int i = 0; i < minSize; ++i){
        if (value & (1UL <<  i)){
            set(i, true);
        }
    }

}

BitArray::BitArray(const BitArray& b) : bits(b.bits), sizeOfBuf(b.sizeOfBuf) {}

void BitArray::swap(BitArray& b){
    std::swap(bits, b.bits);
    std::swap(sizeOfBuf, b.sizeOfBuf);
}

BitArray& BitArray::operator=(const BitArray& b){
    if (this != &b){
        bits = b.bits;
        sizeOfBuf = b.sizeOfBuf;
    }
    return *this;
}

void BitArray::resize(int numBits, bool value){
    if (numBits == 0){
        clear();
        return;
    }

    if (numBits < 0){
        throw std::invalid_argument("index of bits cannot be negative.");
    }

    int diff = numBits - sizeOfBuf;

    if (diff < 0){
        (*this) <<= numBits;
    }


    bits.resize((numBits + bitsPerBlock - 1) / bitsPerBlock, value ? ~0UL : 0UL);
    sizeOfBuf = numBits;

    if (diff > 0){
        (*this) >>= diff;
        for(int i = numBits - diff; i < numBits; ++i){
            set(i, value);
        }
    }
}
 
 
void BitArray::clear(){
    bits.clear();
    sizeOfBuf = 0;
}

void BitArray::pushBack(bool bit){
    resize(sizeOfBuf + 1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b){
    if (sizeOfBuf != b.sizeOfBuf){
        throw std::invalid_argument("sizes must match");
    }

    for (size_t i = 0; i < bits.size(); ++i){
        bits[i] &= b.bits[i];
    }

    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b){
    if (sizeOfBuf != b.sizeOfBuf){
        throw std::invalid_argument("sizes must match");
    }

    for (size_t i = 0; i < bits.size(); ++i){
        bits[i] |= b.bits[i];
    }

    return *this;
}


BitArray& BitArray::operator^=(const BitArray& b){
    if (sizeOfBuf != b.sizeOfBuf){
        throw std::invalid_argument("sizes must match");
    }

    for (size_t i = 0; i < bits.size(); ++i){
        bits[i] ^= b.bits[i];
    }

    return *this;
}


BitArray& BitArray::operator<<=(int n){
    if (n < 0){
        throw std::invalid_argument("shift cannot be negative");
    }
    
    if (n >= sizeOfBuf){
        for (int i = 0; i < sizeOfBuf; ++i){
            reset(i);
        }
        return *this;
    }

    for (int i = 0; i < sizeOfBuf - n; ++i){
        set(sizeOfBuf - i - 1, (*this)[sizeOfBuf - 1 - n - i]);
    }

    for (int i = n - 1; i >= 0; --i){
        set(i, false);
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n){
    if (n < 0){
        throw std::invalid_argument("shift cannot be negative");
    }

  if (n >= sizeOfBuf){
        for (int i = 0; i < sizeOfBuf; ++i){
            reset(i);
        }
        return *this;
    }

    for (int i = 0; i < sizeOfBuf - n; ++i){
        set(i, (*this)[i+n]);
    }

    for (int i = sizeOfBuf - 1; i > sizeOfBuf - n - 1 ; --i){
        set(i, false);
    }

    return *this;
}

BitArray BitArray::operator<<(int n) const{
    BitArray res(*this);
    res <<= n;
    return res;
}

BitArray BitArray::operator>>(int n) const{
    BitArray res(*this);
    res >>= n;
    return res;
}


BitArray& BitArray::set(int n, bool val){
    if (n >= sizeOfBuf || n < 0){
        throw std::invalid_argument("index out of range" );
    }
    if (val){
        bits[(sizeOfBuf - n) / bitsPerBlock] |= (1UL << ((sizeOfBuf - n -1) % bitsPerBlock));
    }
    else{
        bits[(sizeOfBuf - n) / bitsPerBlock] &= ~(1UL << ((sizeOfBuf - n - 1) % bitsPerBlock));
    }
    return *this;
}

BitArray& BitArray::set(){
    std::fill(bits.begin(), bits.end(), ~0UL);
    return *this;
}

BitArray& BitArray::reset(int n){
    return set(n, false);
}

BitArray& BitArray::reset(){
    std::fill(bits.begin(), bits.end(), 0);
    return *this;
}

bool BitArray::any() const{
    for (const auto& block : bits){
        if (block) return true;
    }
    return false;
}

bool BitArray::none() const{
    return !any();
}

BitArray BitArray::operator~() const{
    BitArray res(*this);
    for (auto& block :res.bits){
        block = ~block;
    }
    return res;
}

int BitArray::count() const{
    int counter = 0;

    for (int i = 0; i < sizeOfBuf; ++i){
        counter+=(*this)[i];
    }

    return counter;
}


bool BitArray::operator[](int i) const{
    if (i >= sizeOfBuf || i < 0){
        throw std::invalid_argument("index out of range" );
    }

    return (bits[(sizeOfBuf - i) / bitsPerBlock] >> ((sizeOfBuf - i - 1) % bitsPerBlock)) & 1;
}

int BitArray::size() const{
    return sizeOfBuf;
}

bool BitArray::empty() const{
    return sizeOfBuf == 0;
}

std::string BitArray::toString() const{
    std::string str;
    for (int i = 0; i < sizeOfBuf; ++i){
        str += std::to_string((*this)[sizeOfBuf - i - 1]);
    }
    return str;
}

bool operator==(const BitArray & a, const BitArray & b){
    return ((a.sizeOfBuf == b.sizeOfBuf) && (a.bits == b.bits));
}

bool operator!=(const BitArray & a, const BitArray & b){
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2){
    if(b1.size() != b2.size()){
        throw std::invalid_argument("sizes must match");
    }
    BitArray res(b1);
    res &= b2;
    return res;
}

BitArray operator|(const BitArray& b1, const BitArray& b2){
    if(b1.size() != b2.size()){
        throw std::invalid_argument("sizes must match");
    }
    BitArray res(b1);
    res |= b2;
    return res;
}

BitArray operator^(const BitArray& b1, const BitArray& b2){
    if(b1.size() != b2.size()){
        throw std::invalid_argument("sizes must match");
    }
    BitArray res(b1);
    res ^= b2;
    return res;
}



