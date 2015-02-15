//
//  12bit.h
//  LZW
//
//  Created by Андрей Рычков on 22.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef LZW__16bit_h
#define LZW__16bit_h

#include <bitset>
#include <fstream>
#include "bitstream.h"

struct sixteenBits
{
    unsigned short number;
    sixteenBits setValue(unsigned short num = 0)
    {
        number = num;
        return *this;
    }
};

obitfstream& operator << (obitfstream& out, const sixteenBits& x)
{
    unsigned short tmp = x.number;
    bool a;
    for (int i = 0; i < 16; ++i)
    {
        a = tmp % 2;
        out.putBit(a);
        tmp /= 2;
    }
    return out;
}

ibitfstream& operator >> (ibitfstream& in, sixteenBits& x)
{
    std::bitset<16> bits;
    for (int i = 0; i < 16; ++i)
    {
        bits[i] = in.getBit();
    }
    x.number = bits.to_ulong();
    return in;
}


struct twelveBits
{
    unsigned short number;
    twelveBits setValue(unsigned short num = 0)
    {
        number = num;
        return *this;
    }
};

obitfstream& operator << (obitfstream& out, const twelveBits& x)
{
    unsigned short tmp = x.number;
    bool a;
    for (int i = 0; i < 12; ++i)
    {
        a = tmp % 2;
        out.putBit(a);
        tmp /= 2;
    }
    return out;
}
ibitfstream& operator >> (ibitfstream& in, twelveBits& x)
{
    std::bitset<12> bits;
    for (int i = 0; i < 12; ++i)
    {
        bits[i] = in.getBit();
    }
    x.number = bits.to_ulong();
    return in;
}

#endif